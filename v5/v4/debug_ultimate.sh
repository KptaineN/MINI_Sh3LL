#!/bin/bash
set -u

# ===============================================================================
# SCRIPT DE DÉBOGAGE ULTIME MINISHELL
# ===============================================================================
# Ce script combine toutes les fonctionnalités de débogage :
# - Compilation automatique
# - Tests simples avec timeout
# - Analyse Valgrind complète
# - Débogage GDB avec breakpoints intelligents
# - Intégration minishell_tester (optionnelle)
# - Génération de rapports JSON et HTML
# - Interface interactive pour les crashes
# ===============================================================================

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Variables globales
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
DEBUG_DIR=".debug_ultimate"
TIMESTAMP=$(date --iso-8601=seconds)

# Fichiers de sortie
VG_LOG="$DEBUG_DIR/valgrind.log"
GDB_LOG="$DEBUG_DIR/gdb.log"
GDB_SCRIPT="$DEBUG_DIR/gdb_script.gdb"
TEST_OUTPUT="$DEBUG_DIR/test_output.log"
TESTER_LOG="$DEBUG_DIR/tester_output.log"
SUMMARY_JSON="$DEBUG_DIR/summary.json"
REPORT_HTML="$DEBUG_DIR/report.html"
TEST_COMMANDS="$DEBUG_DIR/test_commands.txt"

# Variables de résultats
COMPILATION_SUCCESS=false
SEGFAULT_DETECTED=false
MEMORY_ERRORS=false
MEMORY_LEAKS=false
TESTER_STATUS="skipped"
TESTER_SUMMARY="N/A"
SUSPECT_LOCATION=""
EXIT_CODE=0

# ===============================================================================
# FONCTIONS UTILITAIRES
# ===============================================================================

print_banner() {
    echo -e "${CYAN}"
    echo "==============================================================================="
    echo "                    DÉBOGAGE ULTIME MINISHELL v2.0"
    echo "==============================================================================="
    echo -e "${NC}"
}

print_section() {
    echo -e "\n${BLUE}=== $1 ===${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_info() {
    echo -e "${CYAN}ℹ️  $1${NC}"
}

prompt_yes_no() {
    local prompt="$1"
    local default="${2:-N}"
    local response
    
    if [ "$default" = "Y" ]; then
        read -r -p "$prompt [Y/n] " response
        response=${response:-Y}
    else
        read -r -p "$prompt [y/N] " response
        response=${response:-N}
    fi
    
    [[ "$response" =~ ^[Yy]$ ]]
}

check_dependencies() {
    print_section "Vérification des dépendances"
    
    local missing_deps=()
    local optional_deps=()
    
    # Dépendances critiques
    for cmd in make gcc; do
        if ! command -v "$cmd" >/dev/null 2>&1; then
            missing_deps+=("$cmd")
        fi
    done
    
    # Dépendances optionnelles
    for cmd in valgrind gdb readelf jq git; do
        if ! command -v "$cmd" >/dev/null 2>&1; then
            optional_deps+=("$cmd")
        fi
    done
    
    if [ ${#missing_deps[@]} -gt 0 ]; then
        print_error "Dépendances critiques manquantes: ${missing_deps[*]}"
        echo "Installe-les avec: sudo apt install ${missing_deps[*]}"
        exit 1
    fi
    
    if [ ${#optional_deps[@]} -gt 0 ]; then
        print_warning "Dépendances optionnelles manquantes: ${optional_deps[*]}"
        echo "Pour un débogage complet, installe: sudo apt install ${optional_deps[*]}"
    fi
    
    print_success "Dépendances vérifiées"
}

setup_environment() {
    print_section "Configuration de l'environnement"
    
    # Créer le dossier de debug
    mkdir -p "$DEBUG_DIR"
    
    # Nettoyer les anciens logs
    rm -f "$DEBUG_DIR"/*.log "$DEBUG_DIR"/*.json "$DEBUG_DIR"/*.html "$DEBUG_DIR"/*.txt
    
    # Créer le fichier de commandes de test par défaut
    cat > "$TEST_COMMANDS" <<'EOF'
pwd
echo "Test automatique minishell"
ls -la
echo $USER
echo $HOME
env | head -5
exit
EOF
    
    print_success "Environnement configuré"
}

# ===============================================================================
# FONCTIONS DE COMPILATION
# ===============================================================================

compile_project() {
    print_section "Compilation du projet"
    
    cd "$PROJECT_ROOT" || exit 1
    
    echo -e "${YELLOW}Nettoyage et recompilation...${NC}"
    if make re > "$DEBUG_DIR/compile.log" 2>&1; then
        COMPILATION_SUCCESS=true
        print_success "Compilation réussie"
    else
        print_error "Erreur de compilation"
        echo "Vérifiez le log: $DEBUG_DIR/compile.log"
        cat "$DEBUG_DIR/compile.log"
        exit 1
    fi
    
    # Vérifier les symboles de debug
    if command -v readelf >/dev/null 2>&1; then
        if readelf --sections ./minishell | grep -q "\.debug_info"; then
            print_success "Symboles de debug détectés"
        else
            print_warning "Pas de symboles de debug. Recompile avec -g -O0 pour un meilleur débogage"
        fi
    fi
}

# ===============================================================================
# FONCTIONS DE TEST
# ===============================================================================

run_simple_test() {
    print_section "Test simple automatique"
    
    local executable="$PROJECT_ROOT/minishell"
    
    if [ ! -x "$executable" ]; then
        print_error "Exécutable minishell introuvable"
        return 1
    fi
    
    echo -e "${CYAN}Exécution des commandes de test...${NC}"
    
    # Test avec timeout
    if timeout 15s "$executable" < "$TEST_COMMANDS" > "$TEST_OUTPUT" 2>&1; then
        local exit_status=$?
        if [ $exit_status -eq 0 ]; then
            print_success "Test simple réussi"
        else
            print_warning "Test terminé avec code de sortie: $exit_status"
            EXIT_CODE=$exit_status
        fi
    else
        local timeout_status=$?
        if [ $timeout_status -eq 124 ]; then
            print_error "TIMEOUT: Le programme a pris trop de temps"
            EXIT_CODE=124
        elif [ $timeout_status -eq 139 ]; then
            print_error "SEGFAULT détecté dans le test simple"
            SEGFAULT_DETECTED=true
            EXIT_CODE=139
        else
            print_warning "Test terminé avec signal: $timeout_status"
            EXIT_CODE=$timeout_status
        fi
    fi
    
    # Analyser la sortie pour détecter des erreurs
    if grep -q "command not found\|No such file\|Permission denied" "$TEST_OUTPUT"; then
        print_warning "Erreurs de commandes détectées dans la sortie"
    fi
}

# ===============================================================================
# FONCTIONS VALGRIND
# ===============================================================================

run_valgrind_analysis() {
    print_section "Analyse Valgrind (mémoire)"
    
    if ! command -v valgrind >/dev/null 2>&1; then
        print_warning "Valgrind non installé, analyse mémoire sautée"
        return 1
    fi
    
    local executable="$PROJECT_ROOT/minishell"
    
    echo -e "${CYAN}Lancement de Valgrind...${NC}"
    valgrind --tool=memcheck \
             --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --verbose \
             --log-file="$VG_LOG" \
             timeout 20s "$executable" < "$TEST_COMMANDS" >/dev/null 2>&1 || true
    
    if [ ! -f "$VG_LOG" ]; then
        print_error "Échec de génération du rapport Valgrind"
        return 1
    fi
    
    # Analyser les résultats
    analyze_valgrind_results
}

analyze_valgrind_results() {
    print_info "Analyse du rapport Valgrind..."
    
    # Détecter les erreurs mémoire
    if grep -qE "Invalid read|Invalid write|Conditional jump" "$VG_LOG"; then
        MEMORY_ERRORS=true
        print_error "Erreurs d'accès mémoire détectées"
        
        # Extraire la localisation suspecte
        SUSPECT_LOCATION=$(awk '
            /Invalid read|Invalid write|Conditional jump/ {
                getline; getline;
                if ($0 ~ /at 0x[0-9A-Fa-f]+:/) {
                    match($0, /\([^)]+:[0-9]+\)/);
                    if (RSTART > 0) {
                        location = substr($0, RSTART+1, RLENGTH-2);
                        gsub(/^.*\//, "", location);
                        print location;
                        exit;
                    }
                }
            }
        ' "$VG_LOG")
        
        if [ -n "$SUSPECT_LOCATION" ]; then
            print_info "Localisation suspecte: $SUSPECT_LOCATION"
        fi
        
        # Afficher un extrait des erreurs
        echo -e "${YELLOW}Extrait des erreurs:${NC}"
        grep -A5 -B2 "Invalid read\|Invalid write\|Conditional jump" "$VG_LOG" | head -20
    else
        print_success "Aucune erreur d'accès mémoire détectée"
    fi
    
    # Détecter les fuites mémoire
    if grep -qE "definitely lost.*[1-9]" "$VG_LOG"; then
        MEMORY_LEAKS=true
        print_error "Fuites mémoire détectées"
        grep -A5 "HEAP SUMMARY\|LEAK SUMMARY" "$VG_LOG"
    else
        print_success "Aucune fuite mémoire majeure"
    fi
    
    # Résumé des erreurs
    echo -e "\n${CYAN}Résumé Valgrind:${NC}"
    grep -A10 "ERROR SUMMARY" "$VG_LOG" | tail -10 || echo "Pas de résumé d'erreurs"
}

# ===============================================================================
# FONCTIONS GDB
# ===============================================================================

run_gdb_analysis() {
    print_section "Analyse GDB (débogage)"
    
    if ! command -v gdb >/dev/null 2>&1; then
        print_warning "GDB non installé, analyse de crash sautée"
        return 1
    fi
    
    generate_gdb_script
    execute_gdb_script
    analyze_gdb_results
}

generate_gdb_script() {
    print_info "Génération du script GDB..."
    
    cat > "$GDB_SCRIPT" <<EOF
set pagination off
set logging file $GDB_LOG
set logging enabled on
set print pretty on
set print array on
set print elements 200

# Configuration pour catch les signaux
catch signal SIGSEGV
catch signal SIGBUS
catch signal SIGFPE

EOF

    # Ajouter des breakpoints intelligents
    if [ -n "$SUSPECT_LOCATION" ]; then
        echo "# Breakpoint sur localisation suspecte de Valgrind" >> "$GDB_SCRIPT"
        if [[ "$SUSPECT_LOCATION" =~ :[0-9]+$ ]]; then
            echo "break $SUSPECT_LOCATION" >> "$GDB_SCRIPT"
        else
            echo "break $SUSPECT_LOCATION" >> "$GDB_SCRIPT"
        fi
    else
        echo "# Breakpoints par défaut" >> "$GDB_SCRIPT"
        echo "break main" >> "$GDB_SCRIPT"
    fi
    
    # Ajouter des breakpoints sur les fonctions critiques
    cat >> "$GDB_SCRIPT" <<EOF

# Breakpoints sur fonctions critiques
break malloc
break free
break execve
break fork

# Exécution du programme
run < $TEST_COMMANDS

echo "\\n=== INFORMATIONS DE CRASH ===""\\n"
info program
info signals

echo "\\n=== BACKTRACE COMPLÈTE ===""\\n"
backtrace full

echo "\\n=== VARIABLES LOCALES ===""\\n"
info locals

echo "\\n=== ARGUMENTS DE FONCTION ===""\\n"
info args

echo "\\n=== REGISTRES ===""\\n"
info registers

echo "\\n=== DISASSEMBLY ===""\\n"
x/20i \$pc

echo "\\n=== MÉMOIRE AUTOUR DE RSP ===""\\n"
x/20x \$rsp

echo "\\n=== VARIABLES GLOBALES ===""\\n"
info variables

# Tentative de navigation dans la stack
echo "\\n=== EXPLORATION DE LA STACK ===""\\n"
frame 0
info locals
frame 1
info locals
frame 2
info locals

quit
EOF
}

execute_gdb_script() {
    print_info "Exécution du script GDB..."
    
    local executable="$PROJECT_ROOT/minishell"
    gdb -batch -x "$GDB_SCRIPT" "$executable" >/dev/null 2>&1 || true
}

analyze_gdb_results() {
    print_info "Analyse des résultats GDB..."
    
    if [ ! -f "$GDB_LOG" ]; then
        print_warning "Pas de log GDB généré"
        return 1
    fi
    
    # Détecter les segfaults
    if grep -qE "Program received signal SIGSEGV|Segmentation fault" "$GDB_LOG"; then
        SEGFAULT_DETECTED=true
        print_error "SEGFAULT détecté par GDB"
        
        # Extraire la stack trace
        echo -e "\n${YELLOW}Stack trace:${NC}"
        grep -A20 "Program received signal\|#0\|#1\|#2\|#3\|#4" "$GDB_LOG" | head -25
        
        # Identifier la fonction problématique
        local problematic_func=$(grep -o "in [a-zA-Z_][a-zA-Z0-9_]* (" "$GDB_LOG" | head -1 | sed 's/in \(.*\) (/\1/')
        if [ -n "$problematic_func" ]; then
            print_info "Fonction problématique probable: $problematic_func"
        fi
        
        # Proposer une session interactive si disponible
        if [ -t 1 ] && prompt_yes_no "Ouvrir une session GDB interactive pour investigation ?"; then
            echo -e "${CYAN}Lancement de GDB interactif...${NC}"
            gdb "$PROJECT_ROOT/minishell" -ex "run < $TEST_COMMANDS"
        fi
    else
        print_success "Aucun segfault détecté par GDB"
    fi
}

# ===============================================================================
# FONCTIONS MINISHELL_TESTER
# ===============================================================================

run_minishell_tester() {
    print_section "Test avec minishell_tester"
    
    local tester_dir="$PROJECT_ROOT/minishell_tester"
    
    # Vérifier si le testeur existe
    if [ ! -d "$tester_dir" ]; then
        if command -v git >/dev/null 2>&1 && prompt_yes_no "Cloner minishell_tester depuis GitHub ?"; then
            print_info "Clonage de minishell_tester..."
            git clone https://github.com/LucasKuhn/minishell_tester.git "$tester_dir" || {
                print_warning "Échec du clonage de minishell_tester"
                TESTER_STATUS="unavailable"
                return 1
            }
        else
            print_warning "minishell_tester non disponible"
            TESTER_STATUS="unavailable"
            return 1
        fi
    fi
    
    # Demander confirmation pour lancer le testeur
    if ! prompt_yes_no "Lancer minishell_tester (peut prendre du temps) ?"; then
        print_info "Test minishell_tester ignoré par l'utilisateur"
        TESTER_STATUS="skipped"
        return 0
    fi
    
    # Exécuter le testeur
    print_info "Exécution de minishell_tester..."
    cd "$tester_dir" || return 1
    
    if ./tester 2>&1 | tee "$TESTER_LOG"; then
        # Analyser les résultats
        local summary_line=$(grep -E '[0-9]+/[0-9]+' "$TESTER_LOG" | tail -1 | tr -d '\r')
        if [ -n "$summary_line" ]; then
            TESTER_SUMMARY="$summary_line"
            if echo "$summary_line" | grep -q "$(echo "$summary_line" | grep -o '^[0-9]*')/\1"; then
                TESTER_STATUS="success"
                print_success "Tous les tests passés: $TESTER_SUMMARY"
            else
                TESTER_STATUS="partial"
                print_warning "Tests partiellement réussis: $TESTER_SUMMARY"
            fi
        else
            TESTER_STATUS="error"
            print_error "Impossible de parser les résultats du testeur"
        fi
    else
        TESTER_STATUS="fail"
        print_error "Échec de l'exécution de minishell_tester"
    fi
    
    cd "$PROJECT_ROOT" || exit 1
}

# ===============================================================================
# FONCTIONS DE RAPPORT
# ===============================================================================

generate_summary_json() {
    print_section "Génération du résumé JSON"
    
    # Échapper les caractères spéciaux pour JSON
    local escaped_suspect_location=$(printf '%s' "$SUSPECT_LOCATION" | sed 's/"/\\"/g')
    
    if command -v jq >/dev/null 2>&1; then
        jq -n \
          --arg timestamp "$TIMESTAMP" \
          --arg suspect_location "$escaped_suspect_location" \
          --argjson compilation_success "$COMPILATION_SUCCESS" \
          --argjson segfault_detected "$SEGFAULT_DETECTED" \
          --argjson memory_errors "$MEMORY_ERRORS" \
          --argjson memory_leaks "$MEMORY_LEAKS" \
          --arg tester_status "$TESTER_STATUS" \
          --arg tester_summary "$TESTER_SUMMARY" \
          --argjson exit_code "$EXIT_CODE" \
          '{
            "timestamp": $timestamp,
            "compilation": {
              "success": $compilation_success
            },
            "simple_test": {
              "exit_code": $exit_code,
              "segfault": $segfault_detected
            },
            "suspect_location": $suspect_location,
            "gdb": {
              "segfault_detected": $segfault_detected
            },
            "valgrind": {
              "memory_errors": $memory_errors,
              "memory_leaks": $memory_leaks
            },
            "minishell_tester": {
              "status": $tester_status,
              "summary": $tester_summary
            }
          }' > "$SUMMARY_JSON"
    else
        # Fallback sans jq
        cat > "$SUMMARY_JSON" <<EOF
{
  "timestamp": "$TIMESTAMP",
  "compilation": {
    "success": $COMPILATION_SUCCESS
  },
  "simple_test": {
    "exit_code": $EXIT_CODE,
    "segfault": $SEGFAULT_DETECTED
  },
  "suspect_location": "$escaped_suspect_location",
  "gdb": {
    "segfault_detected": $SEGFAULT_DETECTED
  },
  "valgrind": {
    "memory_errors": $MEMORY_ERRORS,
    "memory_leaks": $MEMORY_LEAKS
  },
  "minishell_tester": {
    "status": "$TESTER_STATUS",
    "summary": "$TESTER_SUMMARY"
  }
}
EOF
    fi
    
    print_success "Résumé JSON généré: $SUMMARY_JSON"
}

escape_html() {
    sed 's/&/\&amp;/g; s/</\&lt;/g; s/>/\&gt;/g; s/"/\&quot;/g; s/'"'"'/\&#39;/g'
}

generate_html_report() {
    print_section "Génération du rapport HTML"
    
    # Lire les valeurs du JSON
    local compilation_status="unknown"
    local simple_exit_code="unknown"
    local tester_summary_html="N/A"
    local tester_status_html="skipped"
    local suspect_loc_html=""
    
    if command -v jq >/dev/null 2>&1 && [ -f "$SUMMARY_JSON" ]; then
        compilation_status=$(jq -r '.compilation.success' "$SUMMARY_JSON")
        simple_exit_code=$(jq -r '.simple_test.exit_code' "$SUMMARY_JSON")
        tester_summary_html=$(jq -r '.minishell_tester.summary' "$SUMMARY_JSON")
        tester_status_html=$(jq -r '.minishell_tester.status' "$SUMMARY_JSON")
        suspect_loc_html=$(jq -r '.suspect_location' "$SUMMARY_JSON")
    fi
    
    # Extraits des logs
    local valgrind_extract=""
    if [ -f "$VG_LOG" ]; then
        valgrind_extract=$(awk '/Invalid read|Invalid write|Conditional jump/{flag=1} flag{print} /^$/{if(flag){exit}}' "$VG_LOG" | head -30 | escape_html)
    fi
    
    local gdb_extract=""
    if [ -f "$GDB_LOG" ]; then
        gdb_extract=$(grep -A10 "Program received signal\|#0\|#1\|#2\|#3" "$GDB_LOG" | head -20 | escape_html)
    fi
    
    # Classes CSS pour les statuts
    local compilation_class="ok"
    [ "$compilation_status" != "true" ] && compilation_class="fail"
    
    local segfault_class="ok"
    [ "$SEGFAULT_DETECTED" = "true" ] && segfault_class="fail"
    
    local memory_class="ok"
    [ "$MEMORY_ERRORS" = "true" ] && memory_class="fail"
    
    local leaks_class="ok"
    [ "$MEMORY_LEAKS" = "true" ] && leaks_class="warn"
    
    local tester_class="ok"
    case "$tester_status_html" in
        "fail"|"error") tester_class="fail" ;;
        "partial"|"unavailable") tester_class="warn" ;;
    esac
    
    # Génération du HTML
    cat > "$REPORT_HTML" <<EOF
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Rapport de Débogage Ultime - Minishell</title>
  <style>
    * { box-sizing: border-box; }
    body { 
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
      line-height: 1.6; 
      margin: 0; 
      padding: 20px; 
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      min-height: 100vh;
    }
    .container { 
      max-width: 1200px; 
      margin: 0 auto; 
      background: white; 
      border-radius: 12px; 
      box-shadow: 0 20px 40px rgba(0,0,0,0.1);
      overflow: hidden;
    }
    .header { 
      background: linear-gradient(135deg, #2c3e50 0%, #34495e 100%); 
      color: white; 
      padding: 30px; 
      text-align: center; 
    }
    .header h1 { margin: 0; font-size: 2.5em; font-weight: 300; }
    .header p { margin: 10px 0 0 0; opacity: 0.8; }
    .content { padding: 30px; }
    .section { 
      background: #f8f9fa; 
      border-radius: 8px; 
      padding: 20px; 
      margin-bottom: 20px; 
      border-left: 4px solid #007bff;
    }
    .section h2 { 
      margin-top: 0; 
      color: #2c3e50; 
      font-size: 1.4em;
      display: flex;
      align-items: center;
    }
    .section h2::before {
      content: "📊";
      margin-right: 10px;
      font-size: 1.2em;
    }
    .status-grid { 
      display: grid; 
      grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); 
      gap: 15px; 
      margin: 20px 0; 
    }
    .status-item { 
      background: white; 
      padding: 15px; 
      border-radius: 8px; 
      border: 1px solid #dee2e6;
      box-shadow: 0 2px 4px rgba(0,0,0,0.1);
    }
    .status-item h3 { 
      margin: 0 0 10px 0; 
      font-size: 1em; 
      color: #495057; 
    }
    .status { font-weight: bold; font-size: 1.1em; }
    .ok { color: #28a745; }
    .warn { color: #ffc107; }
    .fail { color: #dc3545; }
    .code-block { 
      background: #1e1e1e; 
      color: #d4d4d4; 
      padding: 15px; 
      border-radius: 6px; 
      overflow-x: auto; 
      font-family: 'Courier New', monospace; 
      font-size: 0.9em;
      line-height: 1.4;
      margin: 15px 0;
    }
    .files-list { 
      background: #e9ecef; 
      padding: 15px; 
      border-radius: 6px; 
      margin: 15px 0; 
    }
    .files-list ul { margin: 0; padding-left: 20px; }
    .files-list li { margin: 5px 0; }
    .footer { 
      background: #f8f9fa; 
      padding: 20px; 
      text-align: center; 
      border-top: 1px solid #dee2e6; 
      color: #6c757d; 
    }
    .highlight { background: #fff3cd; padding: 2px 4px; border-radius: 3px; }
  </style>
</head>
<body>
  <div class="container">
    <div class="header">
      <h1>🛠️ Rapport de Débogage Ultime</h1>
      <p>Généré le $TIMESTAMP</p>
    </div>
    
    <div class="content">
      <div class="section">
        <h2>Résumé Exécutif</h2>
        <div class="status-grid">
          <div class="status-item">
            <h3>📦 Compilation</h3>
            <div class="status $compilation_class">$([ "$compilation_status" = "true" ] && echo "Réussie" || echo "Échec")</div>
          </div>
          <div class="status-item">
            <h3>🚀 Test Simple</h3>
            <div class="status $([ "$simple_exit_code" = "0" ] && echo "ok" || echo "warn")">Code de sortie: $simple_exit_code</div>
          </div>
          <div class="status-item">
            <h3>💥 Segfaults</h3>
            <div class="status $segfault_class">$([ "$SEGFAULT_DETECTED" = "true" ] && echo "Détectés" || echo "Aucun")</div>
          </div>
          <div class="status-item">
            <h3>🧠 Erreurs Mémoire</h3>
            <div class="status $memory_class">$([ "$MEMORY_ERRORS" = "true" ] && echo "Détectées" || echo "Aucune")</div>
          </div>
          <div class="status-item">
            <h3>💧 Fuites Mémoire</h3>
            <div class="status $leaks_class">$([ "$MEMORY_LEAKS" = "true" ] && echo "Détectées" || echo "Aucune")</div>
          </div>
          <div class="status-item">
            <h3>🧪 Testeur</h3>
            <div class="status $tester_class">$tester_summary_html</div>
          </div>
        </div>
        
        $([ -n "$suspect_loc_html" ] && echo "<p><strong>🎯 Localisation suspecte:</strong> <code class=\"highlight\">$suspect_loc_html</code></p>")
      </div>
      
      $([ -n "$valgrind_extract" ] && cat <<EOV
      <div class="section">
        <h2>Analyse Valgrind</h2>
        <div class="code-block">$valgrind_extract</div>
      </div>
EOV
)
      
      $([ -n "$gdb_extract" ] && cat <<EOG
      <div class="section">
        <h2>Analyse GDB</h2>
        <div class="code-block">$gdb_extract</div>
      </div>
EOG
)
      
      <div class="section">
        <h2>Fichiers Générés</h2>
        <div class="files-list">
          <ul>
            <li>📊 <strong>Résumé JSON:</strong> <code>$SUMMARY_JSON</code></li>
            <li>🧠 <strong>Log Valgrind:</strong> <code>$VG_LOG</code></li>
            <li>🔍 <strong>Log GDB:</strong> <code>$GDB_LOG</code></li>
            <li>📝 <strong>Sortie test:</strong> <code>$TEST_OUTPUT</code></li>
            $([ "$TESTER_STATUS" != "skipped" ] && echo "<li>🧪 <strong>Log testeur:</strong> <code>$TESTER_LOG</code></li>")
          </ul>
        </div>
      </div>
    </div>
    
    <div class="footer">
      <p>Généré par <strong>debug_ultimate.sh</strong> - Script de débogage combiné pour Minishell</p>
    </div>
  </div>
</body>
</html>
EOF
    
    print_success "Rapport HTML généré: $REPORT_HTML"
}

# ===============================================================================
# FONCTION DE SYNTHÈSE FINALE
# ===============================================================================

print_final_summary() {
    print_section "SYNTHÈSE FINALE"
    
    echo -e "${MAGENTA}📊 Résultats du débogage complet:${NC}\n"
    
    # Statut de compilation
    if [ "$COMPILATION_SUCCESS" = "true" ]; then
        print_success "Compilation réussie"
    else
        print_error "Échec de compilation"
    fi
    
    # Test simple
    if [ "$EXIT_CODE" -eq 0 ]; then
        print_success "Test simple réussi"
    else
        print_warning "Test simple terminé avec code: $EXIT_CODE"
    fi
    
    # Segfaults
    if [ "$SEGFAULT_DETECTED" = "true" ]; then
        print_error "Segfaults détectés"
    else
        print_success "Aucun segfault"
    fi
    
    # Erreurs mémoire
    if [ "$MEMORY_ERRORS" = "true" ]; then
        print_error "Erreurs d'accès mémoire"
    else
        print_success "Accès mémoire OK"
    fi
    
    # Fuites mémoire
    if [ "$MEMORY_LEAKS" = "true" ]; then
        print_warning "Fuites mémoire détectées"
    else
        print_success "Pas de fuites majeures"
    fi
    
    # Testeur
    case "$TESTER_STATUS" in
        "success") print_success "Tous les tests du testeur passés" ;;
        "partial") print_warning "Tests du testeur partiellement réussis: $TESTER_SUMMARY" ;;
        "fail") print_error "Échec des tests du testeur" ;;
        "error") print_error "Erreur lors de l'exécution du testeur" ;;
        "unavailable") print_info "Testeur non disponible" ;;
        "skipped") print_info "Tests du testeur ignorés" ;;
    esac
    
    # Localisation suspecte
    if [ -n "$SUSPECT_LOCATION" ]; then
        echo -e "\n${YELLOW}🎯 Localisation suspecte identifiée: ${SUSPECT_LOCATION}${NC}"
    fi
    
    # Suggestions
    echo -e "\n${CYAN}💡 Suggestions d'amélioration:${NC}"
    
    if [ "$SEGFAULT_DETECTED" = "true" ]; then
        echo "  • Ajoutez des vérifications NULL dans vos fonctions"
        echo "  • Vérifiez les allocations malloc/calloc"
        echo "  • Contrôlez les accès aux tableaux (bounds checking)"
    fi
    
    if [ "$MEMORY_ERRORS" = "true" ]; then
        echo "  • Initialisez toutes vos variables"
        echo "  • Vérifiez la taille des allocations"
        echo "  • Évitez les accès après free()"
    fi
    
    if [ "$MEMORY_LEAKS" = "true" ]; then
        echo "  • Ajoutez des free() correspondants aux malloc()"
        echo "  • Vérifiez votre fonction de nettoyage"
        echo "  • Implémentez une fonction de libération récursive"
    fi
    
    # Fichiers générés
    echo -e "\n${BLUE}📁 Fichiers de débogage générés:${NC}"
    echo "  • $SUMMARY_JSON - Résumé JSON machine-readable"
    echo "  • $REPORT_HTML - Rapport HTML interactif"
    echo "  • $VG_LOG - Log complet Valgrind"
    echo "  • $GDB_LOG - Log complet GDB"
    echo "  • $TEST_OUTPUT - Sortie du test simple"
    if [ "$TESTER_STATUS" != "skipped" ]; then
        echo "  • $TESTER_LOG - Log du testeur minishell"
    fi
    
    # Instructions finales
    echo -e "\n${GREEN}🎉 Analyse terminée avec succès!${NC}"
    echo -e "Ouvre le rapport interactif avec: ${CYAN}xdg-open $REPORT_HTML${NC}"
    
    # Nettoyage optionnel
    echo ""
    if prompt_yes_no "Voulez-vous supprimer les fichiers temporaires ?"; then
        rm -f "$TEST_COMMANDS" "$GDB_SCRIPT"
        print_success "Fichiers temporaires supprimés"
    else
        print_info "Fichiers conservés pour analyse manuelle"
    fi
}

# ===============================================================================
# FONCTION PRINCIPALE
# ===============================================================================

main() {
    # Gérer les interruptions proprement
    trap 'echo -e "\n${RED}Interruption détectée. Nettoyage...${NC}"; exit 130' INT TERM
    
    print_banner
    
    # Initialisation
    check_dependencies
    setup_environment
    
    # Phase de compilation
    compile_project
    
    # Phase de tests
    run_simple_test
    run_valgrind_analysis
    run_gdb_analysis
    
    # Tests avancés (optionnels)
    if prompt_yes_no "Exécuter les tests avancés (minishell_tester) ?"; then
        run_minishell_tester
    fi
    
    # Génération des rapports
    generate_summary_json
    generate_html_report
    
    # Synthèse finale
    print_final_summary
}

# ===============================================================================
# POINT D'ENTRÉE
# ===============================================================================

# Vérifier que le script est lancé depuis le bon répertoire
if [ ! -f "Makefile" ] && [ ! -f "../Makefile" ]; then
    print_error "Ce script doit être lancé depuis le répertoire racine du projet minishell"
    exit 1
fi

# Lancer la fonction principale
main "$@"
