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
push s0
call printf
add esp,4
mov eax,4
push eax
call printh
add esp,4
push s1
call printf
add esp,4
mov ebx,120
push ebx
call printh
add esp,4
add esp,0
l0:
push s2
call printf
add esp,4
add esp,8
ret
section .data:
s0 db "Hello world",0xA,"",0
s1 db "Ok... This is cool though!",0
s2 db "Done",0
