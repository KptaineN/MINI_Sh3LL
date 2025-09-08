#!/bin/bash
set -e

BIN=./minishell

out=$(printf "./test_files/invalid_permission\necho \$?\nexit\n" | $BIN | sed -n '3p')
if [ "$out" != "126" ]; then
    echo "expected 126 but got: $out"
    exit 1
fi

echo "invalid permission test passed"
