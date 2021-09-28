
[extern main]

global printf
global _start
global printh
_start:
	call main
	jmp $	


printf:
	mov ebx, dword [esp+4]
	mov eax, 1
	mov ecx, 0
	mov edx, 0
	int 0x80

	ret


printh:
	mov ebx, dword [esp+4]
	mov eax,2
	mov ecx, 0
	mov edx, 0
	int 0x80
	ret
