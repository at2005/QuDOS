section .text:
global main
[extern QGATE]
[extern qrun]
[extern sendq]
[extern strcpy]
[extern asyncq]
process:
mov edi, 0xA0000000
push 0
l0:
mov eax,100000
mov ebx, dword [esp+0]
cmp ebx,eax
jge l1
push 0
push 0
push 0x0
call esi
add esp,12
push 1
push 0
push 0x5
call esi
add esp,12
push 0
push 0
push 0x1
call esi
add esp,12
push 0
push 31
push 0x6
call esi
add esp,12
mov eax,1
add  dword [esp+0],eax
jmp l0
l1:
add esp,4
push 0
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
mov eax,esp
add eax,0
push eax
push 0
push 0xF
call esi
add esp,12
mov ebx,3
mov ecx, dword [esp+0]
cmp ecx,ebx
jl l2
mov eax,10
l3:
add esp,4
ret
jmp l4
l2:
mov eax,20
l4:
add esp,4
ret
db 0xC0
db 0xDE


l5:
[extern input]
all:
pushad
push edi
push esi
push edx
push ecx
push s0
call print
add esp,4
pop ecx
pop edx
pop esi
pop edi
popad
push num
push edi
push esi
push edx
push ecx
push  dword [esp+16]
call input
add esp,4
pop ecx
pop edx
pop esi
pop edi
l6:
add esp,4
ret
db 0xC0
db 0xDE


[extern print]
main:
mov dword [__q__],ebx
mov esi, QGATE
pushad
push msg_process
push process
call sendq
add esp,8
popad
mov [ebx],byte 0xA
inc ebx
push dword msg_process
push dword ebx
call strcpy
mov ebx,eax
add esp,8
pushad
push all
call asyncq
add esp,4
popad
mov byte [ebx], 0xD
pushad
push dword [__q__]
call qrun
add esp, 4
popad
l7:
ret
db 0xC0
db 0xDE


section .data:
s0 db "hello there",0xA,"",0
msg_process db "process",0
__q__ dd 0

section .bss:
num resb 256
