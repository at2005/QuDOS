

out: qpp
	./qpp test.qpp
	nasm -felf32 out.asm -o out.o
	nasm -felf32 ../shell/sys.asm -o ../shell/sys.o
	ld -melf_i386 ../shell/sys.o out.o -o out.bin


test:

	nasm -felf32 out.asm -o out.o
	nasm -felf32 ../shell/sys.asm -o ../shell/sys.o
	ld -melf_i386 ../shell/sys.o out.o -o out.bin



qpp:
	g++ -m32 main.cpp -o qpp

