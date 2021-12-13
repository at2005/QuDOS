section .text:
global main
[extern quant]
[extern sendq]
[extern execq]
[extern QGATE]
a:
pushad
push dword 0x0
push dword 0x0
mov eax, 0xA0000000
call [eax]
add esp, 8
popad
mov eax,2
mov ebx,1
cmp eax,ebx
jle l0
mov eax,12
mov eax,eax
add esp,0
ret
add esp,0
l0:
db 0xC0
db 0xDE
main:
call quant
mov eax,eax
mov dword [__q__], eax
some_label:
mov ebx,0
pushad
push ebx
push 0x0
call QGATE
add esp, 8
popad
push dword [some_label]
call printh
add esp, 4
pushad
push a
call sendq
add esp,4
popad
mov byte [eax], 0xD
pushad
push dword [__q__]
call execq
add esp, 4
popad
add esp,0
ret
db 0xC0
db 0xDE
section .data:
__q__ dd 0

section .bss:
