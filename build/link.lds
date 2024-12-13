OUTPUT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS {
    . = 0xc0000800;
    .boot : AT(0xf800)
    {
        build/boot.out(.text)
    }

    . = 0xc0000a00;
    .kernel : AT(0xfa00)
    {
        *(.text)
        *(.rodata)
        *(.rodata.*)
        *(.data)
        *(.bss)
        *(COMMON)
        /*build/kernel.o(.text)
        build/kernel.o(.rodata)
        build/kernel.o(.data)
        build/kernel.o(.bss)
        build/kernel.o(COMMON) */
    }
    /DISCARD/ : {
        *(.eh_frame)
        *(.note.gnu.property)
        *(.comment)
    }
}
