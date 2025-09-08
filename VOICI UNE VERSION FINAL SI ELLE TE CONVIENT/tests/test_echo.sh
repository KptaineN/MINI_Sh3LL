#!/bin/bash
set -e

BIN=./minishell

# Single quotes: should not expand
out=$(printf "echo '\$PWD'\nexit\n" | $BIN | sed -n '2p')
if [ "$out" != "\$PWD" ]; then
    echo "expected \$PWD but got: $out"
    exit 1
fi

# Double quotes: should expand
expected=$(pwd)
out=$(printf 'echo "$PWD"\nexit\n' | $BIN | sed -n '2p')
if [ "$out" != "$expected" ]; then
    echo "expected $expected but got: $out"
    exit 1
fi

echo "echo tests passed"

