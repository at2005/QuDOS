section .text:
global main
[extern quant]
[extern sendq]
a:
add esp,0
ret
dd 0xDEADC0DE
main:
call quant
mov eax,eax
mov dword [__q__], eax
pushad
push a
call sendq
 add esp,4
popad
add esp,0
ret
dd 0xDEADC0DE
section .data:
__q__ dd 0

section .bss:
