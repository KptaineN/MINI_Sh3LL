set pagination off
set logging file .debug_combined/gdb_combined.log
set logging enabled on
break main
run < input_trace_log.txt
echo "\n=== Backtrace complète ===\n"
backtrace full
echo "\n=== Variables locales ===\n"
info locals
echo "\n=== Registres ===\n"
info registers
echo "\n=== Disassembly autour du PC ===\n"
x/10i $pc
quit
