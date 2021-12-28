
[extern main]

global printf
global _start
global printh
global scanf
global quant
global zero_buffer
global execq
global sendq


_start:
	call quant
	mov ebx, eax
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


quant:
	mov eax,0
	mov ebx,0
	mov ecx,0
	mov edx,0
	int 0x40
	ret


execq:

	; send quantum data via DMA
	mov ebx, [esp+4]
	mov dword eax, 1
	mov dword ecx, 512
	mov edx, 0
	int 0x40

	; poll until IRQ fires
	call poll

	
	mov eax, 5
	mov ebx, 0
	mov ecx, 0
	mov edx, 0
	int 0x40
	; poll until IRQ happens
	call poll	

	call run

	ret



poll:
	mov eax, 3
	mov ebx,0
	mov ecx, 0
	mov edx, 0
	int 0x40
	cmp eax, 1
	jne poll
	ret

	
run:

	mov eax,2
	mov ebx, 0
	mov ecx, 0
	mov edx,0
	int 0x40
	ret



sendq:
	mov eax, 4
	mov ebx, [esp+4]
	mov ecx, [esp+8]
	mov edx, 0
	int 0x40
	
	ret


zero_buffer:
	mov dword eax, [esp+4]
	mov dword ebx, [esp+8]


	iter:
		mov dword [eax], 0
		inc eax
		dec ebx
		cmp ebx, 0
		jne iter

	ret
		
	
		
global QGATE

QGATE:
	;mov eax, [esp+12]
	mov edi, [esp+4]
	mov [ebx], edi
	inc ebx
	mov edi, [esp+8]
	mov [ebx], edi
	inc ebx	
	ret


