set disassembly intel
target remote localhost:1234
layout asm
layout reg
b *0xf93f
c
add-auto-load-safe-path /home/aldo/code/Normix/.gdbinit
