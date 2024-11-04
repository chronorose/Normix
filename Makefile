<<<<<<< HEAD
CFLAGS := -m32 -mno-sse -ffreestanding -fno-pie -gdwarf-4 -ggdb3 -fno-stack-protector
BUILD := build/
SRC := src/
BOOT := boot/
=======
CFLAGS := -m32 -mno-sse -ffreestanding -fno-pie -gdwarf-4 -ggdb3 -fno-stack-protector -Wall -Wextra -g
BUILD := build/
SRC := src/
>>>>>>> origin/ptntsv_branch
btldr := $(BUILD)boot.bin $(BUILD)boot.img $(BUILD)boot.elf
kernel := $(BUILD)kernel.o $(BUILD)kernel.bin $(BUILD)kernel.tmp
mode := TEXT 

ifdef GRAPHICS
	mode = GRAPHICS
endif

run: link 
<<<<<<< HEAD
	qemu-system-i386 -s -monitor stdio -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0
=======
	qemu-system-i386 -s -S -monitor stdio -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0
>>>>>>> origin/ptntsv_branch

debug: link 
	qemu-system-i386 -s -monitor stdio -S -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

<<<<<<< HEAD
=======

>>>>>>> origin/ptntsv_branch
bochs_debug: link 
	bochs -qf ./setup/bochsrc

bochs_run: link 
	bochs -qf ./setup/bochsrc -rc ./setup/setup

ccompile:
	touch $(kernel)
	rm $(kernel)
<<<<<<< HEAD
	gcc $(CFLAGS) -D$(mode) -c $(wildcard $(SRC)*.c)
	mv *.o $(BUILD)

compile_asm: ccompile
	touch $(btldr)
	rm $(btldr) 

	nasm -f elf $(BOOT)boot.asm -F dwarf -g -d$(mode) -o $(BUILD)boot.out
	nasm -f elf $(SRC)*.asm -F dwarf -g -d$(mode) -o $(BUILD)asm.o

link: compile_asm
	# link compiled kernel with bootloader and make it a binary
	ld -m elf_i386 -o $(BUILD)kernel.elf -T ./build/link.lds $(wildcard $(BUILD)*.o)
=======
	gcc $(CFLAGS) -D$(mode) -c $(SRC)stdlib.c -o $(BUILD)stdlib.o
	gcc $(CFLAGS) -D$(mode) -c $(SRC)trampolines.c -o $(BUILD)trampolines.o
	gcc $(CFLAGS) -D$(mode) -c $(SRC)alloc.c -o $(BUILD)alloc.o
	gcc $(CFLAGS) -D$(mode) -c $(SRC)printer.c -o $(BUILD)printer.o
	gcc $(CFLAGS) -D$(mode) -c $(SRC)kernel.c -o $(BUILD)kernel.o

compile_asm: ccompile
	nasm -f elf32 $(SRC)boot.asm -F dwarf -g -d$(mode) -o $(BUILD)boot.o

link: compile_asm
	ld -m elf_i386 -o $(BUILD)kernel.elf -T ld_script $(BUILD)boot.o $(BUILD)kernel.o $(BUILD)printer.o $(BUILD)stdlib.o $(BUILD)alloc.o $(BUILD)trampolines.o
>>>>>>> origin/ptntsv_branch
	objcopy -g -I elf32-i386 -O binary $(BUILD)kernel.elf $(BUILD)kernel.bin

	dd if=/dev/zero of=$(BUILD)boot.img bs=1024 count=1440
	dd if=$(BUILD)kernel.bin of=$(BUILD)boot.img conv=notrunc seek=0
