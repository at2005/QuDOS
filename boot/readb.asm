read:
	mov ah, 0x02 ; BIOS read function
	

	mov dh,0x0 ; read head 0

	mov ch,0x0 ; read cylinder 0

	mov cl, 0x02 ; read from second sector
	
	mov al,15 ; read 15 sectors
	
	int 0x13 ; call interrupt

	jc error ; if carry flag set, then jump to error message
	
	
	ret ; return 



error:
	mov si, error_msg ; store parameters for print function in SI
	call print ; call print on error message
	jmp $ ; hang
