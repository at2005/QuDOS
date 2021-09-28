
[org 0xC00000]
[bits 32]



mov eax, 1
mov ebx, msg
mov ecx, 0
mov edx, 0
int 0x80


;sti

jmp $

msg db "QOS developed by Ayush Tambde (2021)", 0xA,0xA, "A>",0

