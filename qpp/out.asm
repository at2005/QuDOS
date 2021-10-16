[extern printh]section .text:
global main
main:
mov eax,10
mov ebx,2
cmp eax,ebx
jle l0
mov ecx,2
mov edx,4
add ecx,edx
push ecx
mov ecx,5
add  dword [esp+0],ecx
push  dword [esp+0]
call printh
l0:
mov ecx,3
mov edx,9
add ecx,edx
push ecx
call printh
mov ecx,2
sub  dword [esp+0],ecx
push  dword [esp+0]
call printh
add esp,16
ret