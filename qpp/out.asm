section .text:
global main
[extern QGATE]
[extern qrun]
apply_oracle:
push 0
push 1
push 0x0
call esi
add esp,12
push 1
push 0
push 0x5
call esi
add esp,12
push 0
push 1
push 0x0
call esi
add esp,12
ret
db 0xC0
db 0xDE


diffuse:
push 0
push 0
push 0x0
call esi
add esp,12
push 0
push 1
push 0x0
call esi
add esp,12
push 0
push 0
push 0x1
call esi
add esp,12
push 0
push 1
push 0x1
call esi
add esp,12
push 0
push 1
push 0x0
call esi
add esp,12
push 1
push 0
push 0x5
call esi
add esp,12
push 0
push 1
push 0x0
call esi
add esp,12
push 0
push 1
push 0x1
call esi
add esp,12
push 0
push 0
push 0x1
call esi
add esp,12
push 0
push 1
push 0x0
call esi
add esp,12
push 0
push 0
push 0x0
call esi
add esp,12
ret
db 0xC0
db 0xDE


main:
mov dword [__q__],ebx
mov esi, QGATE
push 0
push 0
push 0x0
call esi
add esp,12
push 0
push 1
push 0x0
call esi
add esp,12
push edi
push esi
push edx
push ecx
push ebx
call apply_oracle
pop ebx
pop ecx
pop edx
pop esi
pop edi
push edi
push esi
push edx
push ecx
push ebx
call diffuse
pop ebx
pop ecx
pop edx
pop esi
pop edi
mov byte [ebx], 0xD
pushad
push dword [__q__]
call qrun
add esp, 4
popad
ret
db 0xC0
db 0xDE


section .data:
__q__ dd 0

section .bss:
