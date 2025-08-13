#!/usr/bin/env bash
set -euo pipefail

LOG_DIR="valgrind_logs"
mkdir -p "$LOG_DIR"

TS=$(date +"%Y%m%d_%H%M%S")
VG_LOG="$LOG_DIR/valgrind.$TS.%p.txt"

exec valgrind \
  --suppressions=readline.supp \
  --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
  --log-file="$VG_LOG" \
  ./minishell

script -q -f "session_$(date +%F_%H-%M-%S).log" \
  valgrind --suppressions=readline.supp \
           --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
           --trace-children=yes \
           --log-file="valgrind.$(date +%F_%H-%M-%S).%p.txt" \
           ./minishell

