[extern printh]
[extern printf]
[extern scanf]
section .text:
global main
main:
mov eax,12
push eax
mov eax,4
push eax
mov eax, dword [esp+4]
cmp eax, dword [esp+0]
jle l0
mov eax,1
push eax
l1:
mov eax,12
mov ebx, dword [esp+0]
cmp ebx,eax
jge l2
mov eax,0
mov ebx, dword [esp+0]
cmp ebx,eax
jne l3
push s0
call printf
add esp,4
add esp,0
l3:
mov eax,1
mov ebx, dword [esp+0]
cmp ebx,eax
jne l4
push s1
call printf
add esp,4
add esp,0
l4:
mov eax,2
mov ebx, dword [esp+0]
cmp ebx,eax
jne l5
push s2
call printf
add esp,4
add esp,0
l5:
mov eax,2
add  dword [esp+0],eax
jmp l1
l2:
add esp,4
l0:
push num
l6:
mov eax,1
mov ebx,1
cmp eax,ebx
jne l7
push s3
call printf
add esp,4
push  dword [esp+0]
call scanf
add esp,4
push  dword [esp+0]
call printf
add esp,4
push s4
call printf
add esp,4
mov eax,0
push eax
l8:
mov eax,10
mov ebx, dword [esp+0]
cmp ebx,eax
jge l9
mov eax,5
mov ebx,1
add  dword [esp+0],ebx
jmp l8
l9:
jmp l6
l7:
add esp,16
ret
section .data:
s0 db "First iteration",0xA,"",0
s1 db "Second iteration",0xA,"",0
s2 db "Third iteration",0xA,"",0
s3 db "A> ",0
s4 db "",0xA,"",0

section .bss:
num resb 256
