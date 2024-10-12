CFLAGS := -m32 -ffreestanding -nostdlib -fno-pie -gdwarf-4 -ggdb3
BUILD := build/

debug: compile
	bochs -qf ./setup/bochsrc

run: compile
	bochs -qf ./setup/bochsrc -rc ./setup/setup

ccompile:
	touch $(BUILD)kernel.o $(BUILD)kernel.tmp $(BUILD)kernel.bin
	rm $(BUILD)kernel.o $(BUILD)kernel.tmp $(BUILD)kernel.bin
	gcc $(CFLAGS) -c -o $(BUILD)kernel.o ./src/kernel.c
	ld -m elf_i386 -o $(BUILD)kernel.elf -Ttext 0xfa00 $(BUILD)kernel.o
	objcopy -O binary $(BUILD)kernel.elf $(BUILD)kernel.bin

compile:ccompile
	touch $(BUILD)boot.bin $(BUILD)boot.img
	rm $(BUILD)boot.bin $(BUILD)boot.img
	nasm -f elf ./src/boot.asm -F dwarf -g -o $(BUILD)boot
	ld -m elf_i386 -o $(BUILD)boot.elf -Ttext 0x7c00 $(BUILD)boot
	objcopy -O binary $(BUILD)boot.elf $(BUILD)boot.bin
	dd if=/dev/zero of=$(BUILD)boot.img bs=1024 count=1440
	dd if=$(BUILD)boot.bin of=$(BUILD)boot.img conv=notrunc
	dd if=$(BUILD)kernel.bin of=$(BUILD)boot.img conv=notrunc seek=1
