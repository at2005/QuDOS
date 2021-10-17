[extern printh]
section .text:
global main
main:
mov eax,10
push eax
mov eax,14
push eax
mov eax, dword [esp+4]
cmp  dword [esp+0],eax
jle l0
mov eax,2
mov ebx,4
add eax,ebx
push eax
mov eax,9
mov ebx, dword [esp+0]
add ebx,eax
push ebx
push  dword [esp+4]
call printh
add esp,4
add esp,8
l0:
add esp,8
ret