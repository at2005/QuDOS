section .text:
global main
[extern QGATE]
[extern qrun]
[extern sendq]
[extern strcpy]
vqe:
mov edi, 0xA0000000
push 2
push 8192
push 0
l0:
mov eax,100
mov ebx, dword [esp+0]
cmp ebx,eax
jge l1
push 0
push 0
l2:
mov eax,1024
mov ebx, dword [esp+0]
cmp ebx,eax
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
mov eax,esp
add eax,0
push eax
push 0
push 0xF
call esi
add esp,12
mov ebx,2
mov ecx, dword [esp+0]
mov ebx,0
mov ebx,ecx
and ebx, 0x1
cmp ebx,0
jne l4
mov ebx,1
add  dword [esp+8],ebx
jmp l5
l4:
mov ebx,1
sub  dword [esp+8],ebx
l5:
mov ebx,1
add  dword [esp+4],ebx
add esp,4
jmp l2
l3:
add esp,4
mov ebx, dword [esp+0]
cmp ebx, dword [esp+8]
jge l6
mov ebx, dword [esp+0]
mov  dword [esp+8],ebx
mov ebx,1
add  dword [esp+12],ebx
jmp l7
l6:
l7:
mov ebx, dword [esp+0]
cmp ebx, dword [esp+8]
jle l8
mov ebx,1
sub  dword [esp+12],ebx
jmp l9
l8:
l9:
mov ebx,1
add  dword [esp+4],ebx
add esp,4
jmp l0
l1:
add esp,4
mov eax, dword [esp+4]
l10:
add esp,8
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
mov byte [ebx], 0xD
pushad
push dword [__q__]
call qrun
add esp, 4
popad
l11:
ret
db 0xC0
db 0xDE


section .data:
msg_vqe db "vqe",0
__q__ dd 0

section .bss:
