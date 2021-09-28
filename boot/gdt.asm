; start gdt

start_gdt:
	; mandatory null descriptor
	gdt_null_desc:
		dd 0x0
		dd 0x0
		
	; code segment descriptor at offset 0x08
	code_segment:
			; first 16 bits of CS limit
			dw 0xFFFF
			; first 16 bits of CS base
			dw 0x0000
			; next 8 bits of CS base
			db 0x00
			; flags
			; 1 for present
			; 00 for privilege level  (highest)
			; 1 for segment type (code)
			; 1 for code segment
			; 0 for conforming -> lower privilege levels cannot access segment
			; 1 for readable
			; 0 for accessed -> CPU will set when accessing segment
			db 10011010b
			
			; flags + last nybble of CS limit
			; 1 for granularity -> shift by 3 nybbles left, allowing access to 32 bits (4GB)
			; 1 for granularity
			; 0 because this is not 64-bit
			; 0 for available (not used for now)
			; Last four bits of limit are 1111b (0xF)
			db 11001111b
			; last byte of base
			db 0x00
	
	; data segment descriptor at offset 0x10 (16)
	data_segment:
			; first 16 bits of DS limit
			dw 0xFFFF
			; first 16 bits of base
			dw 0x0000
			; mid 8 bits of base
			db 0x00
			; flags
			; 1 for present
			; 00 for highest privilege level (ring 0)
			; 1 for segment type
			; 0 for data segment
			; 0 for conforming -> lower privilege levels cannot access segment
			; 1 for readable
			; 0 for accessed -> CPU will set when it accesses this
			db 10010010b
			
			; flags + last nybble of limit (0xF)
			; 11 for granularity
			; 0 because this is not 16 bits
			; 0 available not used
			db 11001111b
			; last 8 bits of base
			db 0x00
			
	user_cs:
		dw 0xFFFF
		dw 0x0000
		db 0x00
		db 11111010b
		
		db 11011111b
		db 0x00
		
	user_ds:
		dw 0xFFFF
		dw 0x0000
		db 0x0
		db 11110010b
		
		db 11011111b
		db 0x00
	
	tss_desc:
		;0x15010
		
		dw 0x0068
		dw 0x5010
		db 0x01
		
		db 11101001b 
		db 00000000b
		
		db 0x00
			
end_gdt:
; gdt descriptor
descriptor:
	; size of GDT - 1
	dw end_gdt-start_gdt-1
	; where GDT starts in memory
	dd start_gdt
	
	
; define macro for CS segment selector
CSGDT equ code_segment - start_gdt
; define macro for DS segmenet selector
DSGDT equ data_segment - start_gdt


