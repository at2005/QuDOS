section .text:
global main
main:
mov eax,9
mov ebx,4
add eax,ebx
mov ecx,8
mov edx,7
imul ecx,edx
add eax,ecx
push eax
