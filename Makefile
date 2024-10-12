CFLAGS := -m32 -ffreestanding -fno-pie -gdwarf-4 -ggdb3
BUILD := build/
SRC := src/
btldr := $(BUILD)boot.bin $(BUILD)boot.img $(BUILD)boot.elf
kernel := $(BUILD)kernel.o $(BUILD)kernel.bin $(BUILD)kernel.tmp

qemu_run: compile
	qemu-system-i386 -s -monitor stdio -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

qemu_debug: compile
	qemu-system-i386 -s -monitor stdio -S -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

debug: compile
	bochs -qf ./setup/bochsrc

run: compile
	bochs -qf ./setup/bochsrc -rc ./setup/setup

ccompile:
	touch $(kernel)
	rm $(kernel)
	gcc $(CFLAGS) -c -o $(BUILD)kernel.o $(SRC)kernel.c
	ld -m elf_i386 -o $(BUILD)kernel.elf -Ttext 0xfa00 $(BUILD)kernel.o
	objcopy -g -I elf32-i386 -O binary $(BUILD)kernel.elf $(BUILD)kernel.bin

compile:ccompile
	touch $(btldr)
	rm $(btldr) 
	nasm -f elf $(SRC)boot.asm -F dwarf -g -o $(BUILD)boot
	objcopy -g -O binary $(BUILD)boot $(BUILD)boot.bin
	ld -m elf_i386 -o $(BUILD)boot.elf -Ttext 0x7c00 $(BUILD)boot
	dd if=/dev/zero of=$(BUILD)boot.img bs=1024 count=1440
	dd if=$(BUILD)boot.bin of=$(BUILD)boot.img conv=notrunc
	dd if=$(BUILD)kernel.bin of=$(BUILD)boot.img conv=notrunc seek=1
