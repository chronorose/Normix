run: all
	qemu-system-i386 -s -monitor stdio -blockdev driver=file,node-name=f0,filename=./build/boot.img -device floppy,drive=f0
all: boot kernel
	dd if=/dev/zero of=./build/boot.img bs=1024 count=1440
	dd if=./build/boot.bin of=./build/boot.img conv=notrunc
	dd if=./build/kernel.bin of=./build/boot.img conv=notrunc seek=1
boot:
	nasm -fbin boot.asm -o ./build/boot.bin
kernel:
	gcc -m32 -fno-pie -ffreestanding -c -o ./build/kernel.o kernel.c
	ld -m i386pe -o ./build/kernel.tmp -Ttext 0xFA00 ./build/kernel.o
	objcopy -I pe-i386 -O binary ./build/kernel.tmp ./build/kernel.bin
clean:
	rm ./build/* mem.dump gen
