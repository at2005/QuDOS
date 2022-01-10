
[extern main]

global print
global _start
global printh
global input
global quant
global zero_buffer
global qrun
global sendq
global strcpy
global strcmp
global asyncq


_start:
	call quant
	mov ebx, eax
	call main
	jmp $	


print:
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


input:
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


strcmp:
	push edi
	push esi
	push edx
	push ecx
	push ebx
	
	mov ebx, [esp+24]
	mov ecx, [esp+28]
	mov edx, 0
	mov esi, 2

	iter_cmp:
		mov dl, byte [ecx]
		cmp dl, [ebx]
		jne neq

		cmp dl, 0
		je eq
		
	;	pushad
	;	push edx
	;	call printh
	;	pop edx
	;	popad
		
		inc ecx
		inc ebx	
		mov edx,0
		jmp iter_cmp
			
			
		
	neq:
		mov eax, 0
		jmp ex
	eq:
		mov eax,1
		jmp ex		

	ex:
	pop ebx
	pop ecx
	pop edx
	pop esi
	pop edi
	;add esp, 8
	ret

strcpy:
	push edi
	push esi
	push edx
	push ecx
	push ebx
	
	mov ebx, 0
	; edx holds what we are copying to
	mov edx, [esp+24]

	; eax holds what we are copying from
	mov eax, [esp+28]


	lp:
		mov bl, [eax]
		mov [edx], bl
		inc eax
		inc edx
		cmp bl, 0
		jne lp

	mov eax, edx	

	pop ebx
	pop ecx
	pop edx
	pop esi
	pop edi
	ret
		
			



quant:
	mov eax,0
	mov ebx,0
	mov ecx,0
	mov edx,0
	int 0x40
	ret


qrun:

	; send quantum data via DMA
	mov ebx, [esp+4]
	mov dword eax, 1
	mov dword ecx, 512
	mov edx, 0
	int 0x40

	; poll until IRQ fires
	call poll

	; send classical data via DMA	
	mov eax, 5
	mov ebx, 0
	mov ecx, 0
	mov edx, 0
	int 0x40
	; poll until IRQ happens
	call poll	

	call run

	ret


poll_fin_irq:
	mov eax, 1
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
	
	cmp eax, 0
	je no_async
	call eax
			
	no_async:

	call poll_fin_irq	
	ret



sendq:
	mov eax, 4
	mov ebx, [esp+4]
	mov ecx, [esp+8]
	mov edx, 0
	int 0x40
	
	ret


asyncq:
	mov eax, 6
	mov ecx, [esp+4]
	mov ebx,0
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
	mov edi, [esp+4]
	mov [ebx], edi
	inc ebx
	mov edi, [esp+8]
	mov [ebx],edi
	inc ebx	
	mov edi, [esp+12]
	mov [ebx], edi
	inc ebx
	ret


