set disassembly intel
target remote localhost:1234
layout asm
layout reg
b funny_things
c
add-auto-load-safe-path /home/aldo/code/Normix/.gdbinit
