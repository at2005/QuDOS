
[extern main]

global printf
global _start
global printh
global scanf


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


scanf:
	mov ebx, dword [esp+4]
	mov eax, 3
	mov ecx, 0
	mov edx, 0
	int 0x80

	
	entlp:
		mov eax, 3
		mov ecx, 1
		int 0x80
		cmp eax, 0
		jne entlp
		
		
	ret

