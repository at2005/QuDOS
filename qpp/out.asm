[extern printh]
[extern printf]
section .text:
global main
main:
push s0
call printf
add esp,4
add esp,0
ret
section .data:
s0 db "Hello world",0
