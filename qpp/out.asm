[extern printh]
[extern printf]
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
push s0
call printf
add esp,4
push  dword [esp+0]
call printh
add esp,4
mov eax,0
mov ebx, dword [esp+0]
cmp ebx,eax
jne l3
push s1
call printf
add esp,4
add esp,0
l3:
mov eax,1
mov ebx, dword [esp+0]
cmp ebx,eax
jne l4
push s2
call printf
add esp,4
add esp,0
l4:
mov eax,2
mov ebx, dword [esp+0]
cmp ebx,eax
jne l5
push s3
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
push  dword [esp+4]
call printh
add esp,4
add esp,8
ret
section .data:
s0 db "Iter: ",0
s1 db "First iteration",0xA,"",0
s2 db "Second iteration",0xA,"",0
s3 db "Third iteration",0xA,"",0
