set disassembly intel
target remote localhost:1234
layout asm
layout reg
b trampoline_0x2a
c
add-auto-load-safe-path /home/aldo/code/Normix/.gdbinit
