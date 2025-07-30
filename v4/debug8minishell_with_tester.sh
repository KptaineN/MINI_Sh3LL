#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== DÉBOGAGE AUTOMATIQUE MINISHELL ===${NC}"

# 1. Compilation avec débogage
echo -e "${YELLOW}=== Compilation avec débogage ===${NC}"
make re

if [ $? -ne 0 ]; then
    echo -e "${RED}Erreur de compilation !${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation réussie !${NC}"

# 2. Test simple automatique
echo -e "\n${YELLOW}=== Test simple automatique ===${NC}"
echo "Test de commandes de base..."

# Créer un fichier de test temporaire
cat > test_commands.txt << 'EOF'
pwd
ls
echo "Hello World"
exit
EOF

echo -e "${BLUE}Exécution des commandes de test...${NC}"
timeout 10s ./minishell < test_commands.txt 2>&1 | tee test_output.log

if [ $? -eq 124 ]; then
    echo -e "${RED}TIMEOUT: Le programme a pris trop de temps${NC}"
elif [ $? -eq 139 ]; then
    echo -e "${RED}SEGFAULT DÉTECTÉ dans le test simple !${NC}"
else
    echo -e "${GREEN}Test simple terminé${NC}"
fi

# 3. Test avec Valgrind automatique
echo -e "\n${YELLOW}=== Test Valgrind automatique ===${NC}"
echo "Recherche de fuites mémoire et erreurs..."

valgrind --tool=memcheck \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind_output.log \
         timeout 10s ./minishell < test_commands.txt 2>&1

# Analyser le rapport Valgrind
if [ -f valgrind_output.log ]; then
    echo -e "${BLUE}Analyse du rapport Valgrind :${NC}"
    
    # Chercher les erreurs critiques
    if grep -q "Invalid read\|Invalid write\|Conditional jump" valgrind_output.log; then
        echo -e "${RED}⚠️  ERREURS MÉMOIRE DÉTECTÉES !${NC}"
        echo "Erreurs trouvées :"
        grep -A2 -B2 "Invalid read\|Invalid write\|Conditional jump" valgrind_output.log
    fi
    
    # Chercher les fuites
    if grep -q "definitely lost\|possibly lost" valgrind_output.log; then
        echo -e "${RED}⚠️  FUITES MÉMOIRE DÉTECTÉES !${NC}"
        grep -A5 "HEAP SUMMARY\|LEAK SUMMARY" valgrind_output.log
    else
        echo -e "${GREEN}✅ Aucune fuite mémoire majeure détectée${NC}"
    fi
    
    # Afficher le résumé
    echo -e "\n${BLUE}Résumé Valgrind :${NC}"
    grep -A10 "ERROR SUMMARY" valgrind_output.log | tail -10
else
    echo -e "${RED}Impossible de générer le rapport Valgrind${NC}"
fi

# 4. Test GDB automatique (pour les segfaults)
echo -e "\n${YELLOW}=== Test GDB automatique ===${NC}"

# Créer un script GDB
cat > gdb_commands.txt << 'EOF'
set pagination off
set logging file gdb_output.log
set logging on
run < test_commands.txt
bt
info registers
quit
y
EOF

echo "Lancement de GDB pour capturer les segfaults..."
timeout 15s gdb -batch -x gdb_commands.txt ./minishell 2>&1

# Analyser la sortie GDB
if [ -f gdb_output.log ]; then
    echo -e "${BLUE}Analyse GDB :${NC}"
    
    if grep -q "Program received signal SIGSEGV\|Segmentation fault" gdb_output.log; then
        echo -e "${RED}🚨 SEGFAULT DÉTECTÉ !${NC}"
        echo "Stack trace :"
        grep -A20 "Program received signal\|#0\|#1\|#2\|#3\|#4" gdb_output.log
        
        # Essayer d'identifier la fonction problématique
        echo -e "\n${YELLOW}Fonction problématique probable :${NC}"
        grep -o "in [a-zA-Z_][a-zA-Z0-9_]* (" gdb_output.log | head -3
    else
        echo -e "${GREEN}✅ Aucun segfault détecté par GDB${NC}"
    fi
else
    echo -e "${YELLOW}GDB n'a pas généré de log (programme peut-être normal)${NC}"
fi

# 5. Résumé automatique
echo -e "\n${BLUE}=== RÉSUMÉ AUTOMATIQUE ===${NC}"

echo -e "${YELLOW}📊 Résultats du débogage :${NC}"

# Vérifier chaque type d'erreur
segfault_detected=false
memory_errors=false
memory_leaks=false

if grep -q "Segmentation fault\|Program received signal SIGSEGV" test_output.log gdb_output.log 2>/dev/null; then
    segfault_detected=true
fi

if [ -f valgrind_output.log ] && grep -q "Invalid read\|Invalid write" valgrind_output.log; then
    memory_errors=true
fi

if [ -f valgrind_output.log ] && grep -q "definitely lost.*[1-9]" valgrind_output.log; then
    memory_leaks=true
fi

# Affichage du résumé
if [ "$segfault_detected" = true ]; then
    echo -e "${RED}❌ Segfaults détectés${NC}"
    echo "  → Vérifiez gdb_output.log pour la stack trace"
else
    echo -e "${GREEN}✅ Aucun segfault${NC}"
fi

if [ "$memory_errors" = true ]; then
    echo -e "${RED}❌ Erreurs d'accès mémoire${NC}"
    echo "  → Vérifiez valgrind_output.log"
else
    echo -e "${GREEN}✅ Accès mémoire OK${NC}"
fi

if [ "$memory_leaks" = true ]; then
    echo -e "${YELLOW}⚠️  Fuites mémoire détectées${NC}"
    echo "  → Vérifiez valgrind_output.log"
else
    echo -e "${GREEN}✅ Pas de fuites majeures${NC}"
fi

# 6. Suggestions automatiques
echo -e "\n${YELLOW}💡 Suggestions automatiques :${NC}"

if [ "$segfault_detected" = true ]; then
    echo "• Ajoutez des vérifications NULL dans vos fonctions"
    echo "• Vérifiez les allocations malloc/calloc"
    echo "• Contrôlez les accès aux tableaux (bounds checking)"
fi

if [ "$memory_errors" = true ]; then
    echo "• Initialisez toutes vos variables"
    echo "• Vérifiez la taille des allocations"
    echo "• Évitez les accès après free()"
fi

if [ "$memory_leaks" = true ]; then
    echo "• Ajoutez des free() correspondants aux malloc()"
    echo "• Vérifiez votre fonction de nettoyage"
fi

# 7. Tests avec minishell_tester
# Cette section exécute automatiquement le testeur (minishell_tester) s'il est
# présent ou peut être cloné depuis GitHub. Un résumé du nombre de tests
# réussis sera affiché. Si certains tests échouent, un avertissement est
# présenté.
echo -e "\n${YELLOW}=== Tests avec minishell_tester ===${NC}"

# État initial
tester_status="not_run"

# Vérifier la présence du dossier de test et le cloner si nécessaire
if [ ! -d "minishell_tester" ]; then
    echo -e "${BLUE}Clonage du dépôt minishell_tester...${NC}"
    if git clone --depth 1 https://github.com/LucasKuhn/minishell_tester.git >/dev/null 2>&1; then
        echo -e "${GREEN}Testeur cloné avec succès${NC}"
    else
        echo -e "${RED}Échec du clonage du testeur, cette étape est ignorée${NC}"
        tester_status="unavailable"
    fi
fi

# Exécuter le testeur si disponible
if [ -d "minishell_tester" ]; then
    echo -e "${BLUE}Lancement des tests du testeur (cela peut prendre un moment)...${NC}"
    pushd minishell_tester >/dev/null || true
    ./tester 2>&1 | tee tester_output.log
    tester_exit=${PIPESTATUS[0]}
    popd >/dev/null || true
    # Extraire la dernière ligne contenant le ratio passé/total
    summary_line=$(grep -E '[0-9]+/[0-9]+' minishell_tester/tester_output.log | tail -n 1 | tr -d '\r')
    if [ -n "$summary_line" ]; then
        echo -e "${BLUE}Résumé du testeur :${NC} $summary_line"
        passed=$(echo $summary_line | awk -F '/' '{print $1}')
        total=$(echo $summary_line | awk -F '/' '{print $2}')
        if [ "$passed" != "$total" ]; then
            tester_status="fail"
        else
            tester_status="success"
        fi
    else
        echo -e "${YELLOW}Impossible d'extraire le résumé des tests du fichier de sortie${NC}"
        tester_status="error"
    fi
fi

# Avertissement selon le statut final
if [ "$tester_status" = "fail" ]; then
    echo -e "${YELLOW}⚠️  Certains tests du testeur ont échoué. Consultez minishell_tester/tester_output.log pour plus de détails.${NC}"
elif [ "$tester_status" = "unavailable" ]; then
    echo -e "${YELLOW}Le testeur n'est pas disponible, aucune exécution effectuée.${NC}"
elif [ "$tester_status" = "error" ]; then
    echo -e "${YELLOW}Une erreur est survenue lors de l'exécution du testeur. Consultez minishell_tester/tester_output.log pour plus d'informations.${NC}"
fi

# Nettoyage
echo -e "\n${BLUE}📁 Fichiers de débogage générés :${NC}"
echo "• test_output.log - Sortie du test simple"
echo "• valgrind_output.log - Rapport Valgrind"
echo "• gdb_output.log - Sortie GDB"
echo "• test_commands.txt - Commandes de test"
echo "• minishell_tester/tester_output.log - Sortie du testeur (si exécuté)"

# Demander si on veut garder les fichiers
echo -e "\n${YELLOW}Voulez-vous supprimer les fichiers temporaires ? (y/N)${NC}"
read -t 5 -n 1 response
if [[ $response =~ ^[Yy]$ ]]; then
    rm -f test_commands.txt gdb_commands.txt
    echo -e "${GREEN}Fichiers temporaires supprimés${NC}"
else
    echo -e "${BLUE}Fichiers conservés pour analyse manuelle${NC}"
fi

echo -e "\n${GREEN}=== DÉBOGAGE AUTOMATIQUE TERMINÉ ===${NC}"