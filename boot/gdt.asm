
start_gdt:

	gdtnul:
		dd 0x0
		dd 0x0
		

	code_segment:
			dw 0xffff
			dw 0x0
			db 0x0
			db 10011010b
			db 11001111b
			db 0x0
		

	data_segment:
			dw 0xffff
			dw 0x0
			db 0x0
			db 10010010b
			db 11001111b
			db 0x0
			
end_gdt:


descriptor:
	dw end_gdt-start_gdt-1
	dd start_gdt
	
	
	
CSGDT equ code_segment - start_gdt
DSGDT equ data_segment - start_gdt

