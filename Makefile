CFLAGS := -m32 -ffreestanding -fno-pie -gdwarf-4 -ggdb3
BUILD := build/
SRC := src/
btldr := $(BUILD)boot.bin $(BUILD)boot.img $(BUILD)boot.elf
kernel := $(BUILD)kernel.o $(BUILD)kernel.bin $(BUILD)kernel.tmp

run: compile
	qemu-system-i386 -s -monitor stdio -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

debug: compile
	qemu-system-i386 -s -monitor stdio -S -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

bochs_debug: compile
	bochs -qf ./setup/bochsrc

bochs_run: compile
	bochs -qf ./setup/bochsrc -rc ./setup/setup

ccompile:
	touch $(kernel)
	rm $(kernel)
	gcc $(CFLAGS) -c -o $(BUILD)kernel.o $(SRC)kernel.c

compile:ccompile
	touch $(btldr)
	rm $(btldr) 

	# assembly bootloader and link it for gdb
	nasm -f elf $(SRC)boot.asm -F dwarf -g -o $(BUILD)boot
	objcopy -g -O binary $(BUILD)boot $(BUILD)boot.bin
	ld -m elf_i386 -o $(BUILD)boot.elf -Ttext 0x7c00 $(BUILD)boot

	# link compiled kernel with bootloader and make it a binary
	ld -m elf_i386 -o $(BUILD)kernel.elf -Ttext 0xf800 $(BUILD)kernel.o $(BUILD)boot
	objcopy -g -I elf32-i386 -O binary $(BUILD)kernel.elf $(BUILD)kernel.bin

	dd if=/dev/zero of=$(BUILD)boot.img bs=1024 count=1440
	dd if=$(BUILD)boot.bin of=$(BUILD)boot.img conv=notrunc
	dd if=$(BUILD)kernel.bin of=$(BUILD)boot.img conv=notrunc seek=1
