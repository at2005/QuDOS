[extern printh]
[extern printf]
section .text:
global main
main:
mov eax,12
push eax
mov eax,4
push eax
mov eax, dword [esp+0]
cmp  dword [esp+4],eax
jle l0
mov eax,0
push eax
l1:
mov eax,10
cmp  dword [esp+0],eax
jge l2
mov eax,5
cmp  dword [esp+0],eax
jle l3
push s0
call printf
add esp,4
add esp,0
l3:
mov eax,1
add  dword [esp+0],eax
jmp l1
l2:
add esp,4
l0:
add esp,8
ret
section .data:
s0 db "Hello world",0xA,"",0
