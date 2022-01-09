section .text:
global main
[extern QGATE]
[extern qrun]
[extern sendq]
[extern strcpy]
[extern asyncq]
[extern input]
vqe:
mov edi, 0xA0000000
push 2
push 8192
push 0
l0:
mov ecx,100
mov edx, dword [esp+0]
cmp edx,ecx
jge l1
push 0
push 0
l2:
mov ecx,1024
mov edx, dword [esp+0]
cmp edx,ecx
jge l3
push 0
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
push  dword [esp+20]
push 0
push 0x6
call esi
add esp,12
push 1
push 0
push 0x5
call esi
add esp,12
mov ecx,esp
add ecx,0
push ecx
push 0
push 0xF
call esi
add esp,12
mov ecx,2
mov edx, dword [esp+0]
mov ecx,0
mov ecx,edx
and ecx, 0x1
cmp ecx,0
jne l4
mov ecx,1
add  dword [esp+8],ecx
jmp l5
l4:
mov ecx,1
sub  dword [esp+8],ecx
l5:
mov ecx,1
add  dword [esp+4],ecx
add esp,4
jmp l2
l3:
add esp,4
mov ecx, dword [esp+0]
cmp ecx, dword [esp+8]
jge l6
mov ecx, dword [esp+0]
mov  dword [esp+8],ecx
mov ecx,1
add  dword [esp+12],ecx
jmp l7
l6:
l7:
mov ecx, dword [esp+0]
cmp ecx, dword [esp+8]
jle l8
mov ecx,1
sub  dword [esp+12],ecx
jmp l9
l8:
l9:
mov ecx,1
add  dword [esp+4],ecx
add esp,4
jmp l0
l1:
add esp,4
mov ecx,1024
push edx
push eax
mov NONE_FREE,1024
mov edx,0
mov eax, dword [esp+8]
idiv NONE_FREE
mov NONE_FREE,eax
pop eax
pop edx
mov  dword [esp+8],NONE_FREE
mov eax, dword [esp+0]
l10:
add esp,8
ret
db 0xC0
db 0xDE


all:
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
l11:
add esp,4
ret
db 0xC0
db 0xDE


main:
mov dword [__q__],ebx
mov esi, QGATE
pushad
push msg_vqe
push vqe
call sendq
add esp,8
popad
mov [ebx],byte 0xA
inc ebx
push dword msg_vqe
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
l12:
ret
db 0xC0
db 0xDE


section .data:
msg_vqe db "vqe",0
__q__ dd 0

section .bss:
num resb 256
