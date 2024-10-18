set disassembly intel
target remote localhost:1234
layout asm
layout reg
b *0x7c56
c
add-auto-load-safe-path /home/aldo/code/Normix/.gdbinit
