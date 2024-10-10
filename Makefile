debug: compile
	bochs -qf ./setup/bochsrc

run: compile
	bochs -qf ./setup/bochsrc -rc ./setup/setup

compile:
	touch ./build/boot.bin ./build/boot.img
	rm ./build/boot.bin ./build/boot.img
	nasm -fbin boot.asm -g -o ./build/boot.bin
	dd if=/dev/zero of=./build/boot.img bs=1024 count=1440
	dd if=./build/boot.bin of=./build/boot.img conv=notrunc
	dd if=./gen of=./build/boot.img conv=notrunc seek=1
