global enter_user_mode

global tss_start
global user_func

[extern print_hex]
[extern usr_init]


tss_start:
	link dw 0
	link_rsrv dw 0
	esp0 dd 0
	ss0 dw 0
	ss0_rsrv dw 0
	esp1 dd 0
	ss1 dw 0
	ss1_rsrv dw 0
	esp2 dd 0
	ss2 dw 0
	ss2_rsrv dw 0
	ctr3 dd 0
	eip_tss dd 0
	eflags_tss dd 0
	eax_tss dd 0
	ecx_tss dd 0
	edx_tss dd 0
	ebx_tss dd 0
	esp_tss dd 0
	ebp_tss dd 0
	esi_tss dd 0
	edi_tss dd 0
	es_tss dw 0
	es_rsrv dw 0
	cs_tss dw 0
	cs_rsrv dw 0
	ss_tss dw 0
	ss_rsrv dw 0
	ds_tss dw 0
	ds_rsrv dw 0
	fs_tss dw 0
	fs_rsrv dw 0
	gs_tss dw 0
	gs_rsrv dw 0
	ldtr_tss dw 0
	ldtr_rsrv dw 0
	iopb_rsrv dw 0
	iopb_tss dw 0
end_tss:

sizeoftss equ end_tss - tss_start	

enter_user_mode:

	mov [esp0], esp
	mov [ss0], ss
	
	mov ax, (0x28 | 3)
	ltr ax
	
	
	mov ax, 0x23
	mov ds, ax
	mov gs, ax
	mov es, ax
	mov fs, ax
	
	; set up stack so iret exits into user mode
	mov ebx, 0x09000FE6
	; data segment descriptor
	push 0x23
	; stack
	push ebx
	; flags
	pushf
	; push CS descriptor       
	push (0x18 | 3)
	
	; push code to jump to
	push 0x08049000
	iret 

user_func:
	;pusha
	;mov eax, 0xB8000
	;mov [eax], byte 'a'
	call 0x00C00000
	;popa
	ret	
	
msg db "hello there!"

	
	
