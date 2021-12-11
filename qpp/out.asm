section .text:
global main
[extern quant]
[extern sendq]
[extern execq]
a:
mov eax,5
mov eax,eax
add esp,0
ret
db 0xC0
db 0xDE
main:
call quant
mov eax,eax
mov dword [__q__], eax
mov ebx,0
mov byte [eax],0x0
inc eax
mov byte [eax],bl
inc eax
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
