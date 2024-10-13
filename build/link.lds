OUTPUT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS {
    . = 0x0;
    .boot : AT(0x7c00)
    {
        build/boot.out(.text)
    }

    . = 0xfa00;
    .kernel : AT(0x7e00)
    {
        *(.text)
        *(.rodata)
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
