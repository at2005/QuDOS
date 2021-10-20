[extern printh]
[extern printf]
section .text:
global main
main:
mov eax,4
mov ebx,2
cmp eax,ebx
jle l0
mov ecx,2
push ecx
call printf
add esp,4
add esp,0
l0:
push s0
call printf
add esp,4
add esp,0
ret
section .data:
s0 db "Hello world",0
