


print:       	; subroutine for print
	mov ah, 0x0e ; BIOS print function
	lodsb 	; load ASCII character from SI register into AH
	int 0x10 	; Call BIOS interrupt
	cmp byte [si],0 	; check if byte is NULL, e.g. we're at the end of string
	jne print 	; if not zero then loop
	ret ; return
	
	


