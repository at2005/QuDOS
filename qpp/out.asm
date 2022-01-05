section .text:
global main
[extern print]
[extern qrun]
[extern printh]
[extern zero_buffer]
[extern quant]
[extern input]
[extern QGATE]
[extern sendq]
main:
mov dword [__q__],ebx
mov esi, QGATE
push 21
mov ecx,5
mov edx, dword [esp+0]
cmp edx,ecx
jge l0
push edi
push esi
push edx
push ecx
push ebx
push 2
call printh
add esp,4
pop ebx
pop ecx
pop edx
pop esi
pop edi
jmp l1
l0:
push edi
push esi
push edx
push ecx
push ebx
push 3
call printh
add esp,4
pop ebx
pop ecx
pop edx
pop esi
pop edi
l1:
push edi
push esi
push edx
push ecx
push ebx
push s0
call print
add esp,4
pop ebx
pop ecx
pop edx
pop esi
pop edi
l2:
add esp,4
ret
db 0xC0
db 0xDE


section .data:
s0 db "okay!",0
__q__ dd 0

section .bss:
