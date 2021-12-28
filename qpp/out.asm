section .text:
global main
[extern quant]
[extern sendq]
[extern execq]
[extern QGATE]
[extern printh]
[extern printf]
stuff:
mov edi, 0xA0000000
push 0
push 0x0
call esi
add esp,8
mov eax,5
add esp,0
ret
db 0xC0
db 0xDE


main:
mov dword [__q__],ebx
mov esi, QGATE
push 0
push 0x0
call esi
add esp,8
pushad
push msg_stuff
push stuff
call sendq
add esp,8
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
msg_stuff db "stuff",0
__q__ dd 0

section .bss:
