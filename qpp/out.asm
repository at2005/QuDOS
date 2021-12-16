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
mov eax,0
push eax
push 0x0
call esi
add esp,8
mov ecx,5
mov eax,ecx
add esp,0
ret
db 0xC0
db 0xDE
main:
mov dword [__q__],ebx
mov esi, QGATE
mov eax,0
push eax
push 0x0
call esi
add esp,8
call a
add esp,0
pushad
push a
call sendq
 add esp,4
popad
mov byte [ebx], 0xD
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
