section .text:
global main
[extern printf]
[extern execq]
[extern printh]
[extern zero_buffer]
[extern quant]
[extern scanf]
[extern QGATE]
newline:
push s0
call printf
add esp,4
add esp,0
ret
db 0xC0
db 0xDE


main:
mov dword [__q__],ebx
mov esi, QGATE
push dword 0b1000001010010000000000000000000
fld dword [esp]
add esp,4
push dword 0b1000000010110011001100110011010
fld dword [esp]
add esp,4

fadd
fstp dword [val]
push dword [val]
call printh
add esp,4

push s1
push  dword [esp+0]
call printf
add esp,4
push num
l0:
mov eax,1
cmp eax,1
jne l1
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
push 256
push  dword [esp+4]
call zero_buffer
add esp,8
jmp l0
l1:
add esp,8
ret
db 0xC0
db 0xDE


section .data:
s0 db "",0xA,"",0
s1 db "Command Shell For Hybrid Classical/Quantum OS Programmed By Ayush Tambde",0xA,"For BTYSTE 2022",0xA,"This is a multi-tasking kernel with paging enabled",0xA,"Type INFO for more information",0xA,"Type HELP for a basic user guide",0xA,"",0xA,"",0
s2 db "A> ",0
__q__ dd 0
val dd 0
section .bss:
num resb 256
