section .text:
global main
[extern printf]
[extern execq]
[extern printh]
[extern zero_buffer]
[extern quant]
newline:
push s0
call printf
add esp,4
add esp,0
ret
main:
call quant
mov eax,eax
mov dword [__q__], eax
mov ebx,0
mov byte [eax],0x1
inc eax
mov byte [eax],bl
inc eax
mov ebx,0
mov byte [eax],0x0
inc eax
mov byte [eax],bl
inc eax
mov ebx,2
mov byte [eax],0x1
inc eax
mov byte [eax],bl
inc eax
mov ebx,3
mov byte [eax],0x0
inc eax
mov byte [eax],bl
inc eax
mov ebx,2
mov byte [eax],0x3
inc eax
mov byte [eax],bl
inc eax
mov ebx,1
mov byte [eax],0x2
inc eax
mov byte [eax],bl
inc eax
mov byte [eax], 0xD
pushad
push dword [__q__]
call execq
add esp, 4
popad
add esp,0
ret
section .data:
s0 db "",0xA,"",0
__q__ dd 0

section .bss:
