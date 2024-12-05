set disassembly intel
target remote localhost:1234
layout asm
layout reg
b kmain
c
add-auto-load-safe-path /home/aldo/code/Normix/.gdbinit
