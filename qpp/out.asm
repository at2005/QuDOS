[extern printh]
[extern printf]
[extern scanf]
[extern zero_buffer]
section .text:
global main
newline:
push s0
call printf
add esp,4
add esp,0
ret
main:
mov eax,12
push eax
mov eax,4
push eax
mov eax, dword [esp+4]
cmp eax, dword [esp+0]
jle l0
mov eax,10
push eax
l1:
mov eax,0
mov ebx, dword [esp+0]
cmp ebx,eax
jl l2
mov eax,1
sub  dword [esp+0],eax
jmp l1
l2:
add esp,4
l0:
push s1
push  dword [esp+0]
call printf
add esp,4
push num
l3:
mov eax,1
mov ebx,1
cmp eax,ebx
jne l4
push s2
call printf
add esp,4
push  dword [esp+0]
call scanf
add esp,4
push  dword [esp+0]
call printf
add esp,4
call newline
add esp,0
mov eax,256
push eax
push  dword [esp+4]
call zero_buffer
add esp,8
jmp l3
l4:
add esp,16
ret
section .data:
s0 db "",0xA,"",0
s1 db "Q++ Shell For QOS Programmed By Ayush Tambde",0xA,"",0
s2 db "A> ",0

section .bss:
num resb 256
