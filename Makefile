CFLAGS := -m32 -mno-sse -ffreestanding -fno-pie -gdwarf-4 -ggdb3 -fno-stack-protector
BUILD := build/
SRC := src/
BOOT := boot/
btldr := $(BUILD)boot.bin $(BUILD)boot.img $(BUILD)boot.elf
kernel := $(BUILD)kernel.o $(BUILD)kernel.bin $(BUILD)kernel.tmp
mode := TEXT 

ifdef GRAPHICS
	mode = GRAPHICS
endif

run: link 
	qemu-system-i386 -s -monitor stdio -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

debug: link 
	qemu-system-i386 -s -monitor stdio -S -blockdev driver=file,node-name=f0,filename=$(BUILD)boot.img -device floppy,drive=f0

bochs_debug: link 
	bochs -qf ./setup/bochsrc

bochs_run: link 
	bochs -qf ./setup/bochsrc -rc ./setup/setup

ccompile:
	touch $(kernel)
	rm $(kernel)
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
	objcopy -g -I elf32-i386 -O binary $(BUILD)kernel.elf $(BUILD)kernel.bin

	dd if=/dev/zero of=$(BUILD)boot.img bs=1024 count=1440
	dd if=$(BUILD)kernel.bin of=$(BUILD)boot.img conv=notrunc seek=0
