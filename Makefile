IMG_PATH = ./build/boot.img
SRC = ./test.asm
run: compile
	qemu-system-x86_64 -blockdev driver=file,node-name=f0,filename=$(IMG_PATH) -device floppy,drive=f0

compile:
	touch ./build/boot.bin ./build/boot.img
	rm ./build/boot.bin ./build/boot.img
	nasm -fbin $(SRC) -o ./build/boot.bin
	dd if=/dev/zero of=./build/boot.img bs=1024 count=1440
	dd if=./build/boot.bin of=./build/boot.img conv=notrunc
