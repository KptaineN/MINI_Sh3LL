#!/bin/bash

# debug léger : montre ce qui s'exécute
set -x

# Arguments
EXE="$1"
INPUT="$2"

if [ -z "$EXE" ] || [ -z "$INPUT" ]; then
  echo "Usage: $0 <exécutable> <fichier_d'entrée>"
  exit 1
fi

if [ ! -x "$EXE" ]; then
  echo "Erreur : '$EXE' non exécutable"
  exit 1
fi

if [ ! -f "$INPUT" ]; then
  echo "Erreur : fichier d'entrée '$INPUT' introuvable"
  exit 1
fi

mkdir -p .debug_combined
VG_LOG=".debug_combined/valgrind.log"
GDB_LOG=".debug_combined/gdb_combined.log"
SUMMARY="summary.json"
REPORT="report.html"

# 1. Valgrind (tolère l'échec)
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes \
    --verbose --log-file="$VG_LOG" timeout 15s "$EXE" < "$INPUT" >/dev/null 2>&1 || true

# 2. GDB : breakpoint sur main et snapshot
cat > .debug_combined/gdb_script.gdb <<EOF
set pagination off
set logging file $GDB_LOG
set logging enabled on
break main
run < $INPUT
backtrace full
info locals
info registers
x/10i \$pc
quit
EOF

gdb -batch -x .debug_combined/gdb_script.gdb "$EXE" >/dev/null 2>&1 || true

# 3. Analyse sommaire
segfault=false
if grep -qE "Program received signal SIGSEGV|Segmentation fault" "$GDB_LOG"; then
  segfault=true
fi

memory_errors=false
if grep -qE "Invalid read|Invalid write|Conditional jump" "$VG_LOG"; then
  memory_errors=true
fi

memory_leaks=false
if grep -qE "definitely lost.*[1-9]" "$VG_LOG"; then
  memory_leaks=true
fi

timestamp=$(date --iso-8601=seconds)

# 4. Génération JSON
cat > "$SUMMARY" <<EOF
{
  "timestamp": "$timestamp",
  "gdb": {
    "segfault_detected": $segfault
  },
  "valgrind": {
    "memory_errors": $memory_errors,
    "memory_leaks": $memory_leaks
  }
}
EOF

# 5. Rapport HTML simple
cat > "$REPORT" <<EOF
<!doctype html>
<html>
<head><meta charset="utf-8"><title>Rapport debug</title></head>
<body>
  <h1>Résumé de debug</h1>
  <pre>$(sed 's/&/\&amp;/g' "$SUMMARY")</pre>
  <h2>Logs</h2>
  <p>Valgrind: <code>$VG_LOG</code></p>
  <p>GDB: <code>$GDB_LOG</code></p>
</body>
</html>
EOF

echo "Analyse terminée. Fichiers générés:"
echo "  - $SUMMARY"
echo "  - $REPORT"
echo "  - $VG_LOG"
echo "  - $GDB_LOG"
