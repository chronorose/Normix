run: all
	qemu-system-x86_64 -s -monitor stdio -blockdev driver=file,node-name=f0,filename=./build/boot.img -device floppy,drive=f0

all: boot
	dd if=/dev/zero of=./build/boot.img bs=1024 count=1440
	dd if=./build/boot.bin of=./build/boot.img conv=notrunc
	dd if=./gen of=./build/boot.img conv=notrunc seek=1

boot:
	nasm -fbin boot.asm -o ./build/boot.bin

kloader:
	nasm -fbin kloader.asm -o ./build/kloader.bin
clean:
	rm ./build/* mem.dump gen
