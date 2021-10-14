section .text:
global main
main:
mov eax,7
mov ebx,2
cmp eax,ebx
and ecx,0x0
setg cl
push ecx
