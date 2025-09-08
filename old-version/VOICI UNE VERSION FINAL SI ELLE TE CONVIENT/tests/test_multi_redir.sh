#!/bin/bash
set -e

BIN=./minishell
OUTDIR=./test_files
rm -f $OUTDIR/out1 $OUTDIR/out2

out=$(printf "echo hi > $OUTDIR/out1 > $OUTDIR/out2\nexit\n" | $BIN 2>&1 || true)
if echo "$out" | grep -q "command not found"; then
    echo "unexpected command execution: $out"
    exit 1
fi

if [ ! -f $OUTDIR/out2 ] || [ "$(cat $OUTDIR/out2)" != "hi" ]; then
    echo "expected hi in out2 but got: $(cat $OUTDIR/out2 2>/dev/null)"
    exit 1
fi

echo "multiple redirection test passed"
