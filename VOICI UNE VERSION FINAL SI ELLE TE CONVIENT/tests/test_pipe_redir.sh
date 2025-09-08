#!/bin/bash
set -e

BIN=./minishell

# Ensure cat reads from file despite pipe input
out=$(printf "echo hi | cat < ./test_files/infile\nexit\n" | $BIN | sed -n '2p')
if [ "$out" != "from_file" ]; then
    echo "expected from_file but got: $out"
    exit 1
fi

# Pipeline with builtin as second command
expected=$(pwd)
out=$(printf "/bin/echo hi | pwd\nexit\n" | $BIN | sed -n '2p')
if [ "$out" != "$expected" ]; then
    echo "expected $expected but got: $out"
    exit 1
fi

# Pipeline with redirections on both sides
tmp_out=$(mktemp)
printf "cat < ./test_files/infile | wc -l > $tmp_out\nexit\n" | $BIN > /dev/null
out=$(cat "$tmp_out" | tr -d ' ')
rm -f "$tmp_out"
if [ "$out" != "1" ]; then
    echo "expected 1 but got: $out"
    exit 1
fi

# Redirection before second command in pipeline
tmp_out=$(mktemp)
printf "echo hi | >$tmp_out cat\nexit\n" | $BIN > /dev/null
status=$?
out=$(cat "$tmp_out" | tr -d '\n')
rm -f "$tmp_out"
if [ "$status" -ne 0 ] || [ "$out" != "hi" ]; then
    echo "redir after pipe failed: status=$status out=$out"
    exit 1
fi

# Exit status reflects second command
tmp_out=$(mktemp)
printf "echo hi | >$tmp_out /bin/false\nexit\n" | $BIN > /dev/null
status=$?
rm -f "$tmp_out"
if [ "$status" -eq 0 ]; then
    echo "expected non-zero exit status"
    exit 1
fi

echo "pipe tests passed"
