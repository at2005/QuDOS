
print_hexb:
	mov ax, si
	and ax, 0xF
	mov ah, 0x0e
	add al, byte 48
	cmp al, byte 58
	jge alpha_hex
	
r_lbl:	int 0x10
	shr si, 4
	cmp si, word 0
	jne print_hexb	
	ret
	
	alpha_hex:
		add al, byte 7
		jmp  r_lbl
		
