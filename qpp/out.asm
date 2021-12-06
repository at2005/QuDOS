[extern printh]
[extern printf]
[extern scanf]
[extern zero_buffer]
[extern quant]
section .text:
global main
newline:
push s0
call printf
add esp,4
add esp,0
ret
main:
call quant
mov eax,eax
mov ebx,0
mov byte [eax],0xA
inc eax
mov byte [eax],bl
inc eax
add esp,0
ret
section .data:
s0 db "",0xA,"",0

section .bss:
