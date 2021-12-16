section .text:
global main
[extern quant]
[extern sendq]
[extern execq]
[extern QGATE]
[extern printh]
[extern printf]
a:
mov edi, 0xA0000000
pushad
push dword 0x0
push dword 0x0
call [edi]
add esp, 8
popad
mov eax,0
push eax
push 0x3
call esi
add esp, 8
mov ebx,2
mov eax,ebx
add esp,0
ret
db 0xC0
db 0xDE
main:
call quant
mov eax,eax
mov dword [__q__], eax
mov esi, QGATE
mov ecx,0
push ecx
push 0x0
call esi
add esp, 8
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
