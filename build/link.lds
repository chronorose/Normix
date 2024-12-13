OUTPUT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS {
    . = 0xf800;
    .boot :
    {
        build/boot.out(.text)
    }

    . = 0xfa00;
    .kernel :
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
