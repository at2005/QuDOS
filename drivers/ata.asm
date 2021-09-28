
global read_ata
global write_ata





read_ata:
	mov edi, [esp+4]
	mov al, 0xE0
	mov dx, 0x1F6
	out dx,al
	
	mov al, 0x0
	mov dx,0x1F2
	out dx,al
	inc dx
	out dx,al
	inc dx
	out dx,al
	inc dx
	out dx,al
	
	mov al, 0x20
	out dx,al
	
	mov ecx, 256
	mov dx, 0x1F0
	rep insw 
	
	ret
	
	
	
	
write_ata:
	mov esi, [esp+4]
	mov al, 0xE0
	mov dx, 0x1F6
	out dx,al
	
	mov al, 0x0
	mov dx,0x1F2
	out dx,al
	inc dx
	out dx,al
	inc dx
	out dx,al
	inc dx
	out dx,al
	
	mov al, 0x30
	out dx,al
	
	mov ecx, 255
	mov dx, 0x1F0
	rep outsw
	ret
	

	
