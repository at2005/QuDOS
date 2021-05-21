nasm -f bin -o boot/boot.bin boot/boot.asm

gcc -ffreestanding -m32 -fno-pie -c kernel/kernel.c -o kernel/kernel.o

nasm -felf32 -o kernel/lkernel.o kernel/lkernel.asm
nasm -felf32 -o kernel/irq.o kernel/irq.asm
echo "Finished assembling..."

ld -o kernel/kernel.tmp -Ttext 0x1000 kernel/lkernel.o kernel/irq.o kernel/kernel.o -mi386pe
objcopy -O binary kernel/kernel.tmp kernel/kernel.bin


cat boot/boot.bin kernel/kernel.bin > osimage

#qemu-system-i386 -d int -no-reboot -no-shutdown osimage
qemu-system-i386 osimage
