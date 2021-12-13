#!/bin/bash

dd if=/dev/zero of=harddisk.img bs=256 count=1600

nasm -f bin -o boot/boot.bin boot/boot.asm
nasm -f bin -o test.bin test.asm
nasm -felf32 -o test2.o test2.asm
ld test2.o -melf_i386 -o test2.bin
rm test2.o

nasm -felf32 -o shell/sys.o shell/sys.asm

gcc -Wall -ffreestanding -fno-pie -m32 -c shell/shell.c -o shell/shell.o
#ld shell/sys.o shell/shell.o -o shell/shell.bin -melf_i386

cd qpp
make
cd -

dd if=test2.bin of=harddisk.img bs=1 count=8192 seek=4096x6 conv=notrunc
dd if=qpp/out.bin of=harddisk.img bs=1 count=9000 seek=4096x8 conv=notrunc
#dd if=shell/shell.bin of=harddisk.img bs=1 count=9000 seek=4096x8 conv=notrunc
gcc -ffreestanding -m32 -fno-pie -c kernel/kernel.c -o kernel/kernel.o

nasm -felf32 -o kernel/lkernel.o kernel/lkernel.asm
nasm -felf32 -o kernel/irq.o kernel/irq.asm
nasm -felf32 -o memory/set_paging.o memory/set_paging.asm
nasm -felf32 -o processes/tss.o processes/tss.asm

echo "Finished assembling..."

ld -mi386pe -o kernel/kernel.tmp -T link.ld 
#objdump -x kernel/kernel.tmp

objcopy -O binary kernel/kernel.tmp kernel/kernel.bin


cat boot/boot.bin kernel/kernel.bin > osimage.img

dd if=/dev/zero of=drive.img bs=1024 count=1440
dd if=osimage.img of=drive.img conv=notrunc seek=0

cp drive.img iso/
genisoimage -quiet -V "MYOS" -input-charset iso8859-1 -o osimage.iso -b drive.img -hide drive.img iso/

../qemu-custom/QEMU-Quantum-PCI-Device/qemu/build/i386-softmmu/qemu-system-i386 -fda drive.img -hda harddisk.img -m 1000M --device qc  

rm osimage.img
rm  memory/*.o
rm  kernel/*.o
rm drivers/*.o
rm processes/*.o
rm -r kernel/*.bin
rm programs/*.bin
rm osimage.img
rm -r kernel/*.tmp
rm shell/*.o
rm shell/*.bin
rm -r *.bin
