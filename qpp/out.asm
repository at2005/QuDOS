[extern printh]
[extern printf]
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
