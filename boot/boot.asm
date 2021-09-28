
[bits 16] ; 16 bit mode

[org 0x7c00] ; start executing at 0x7c00

mov bp, 0x7000 ; set up stack
mov sp,bp ; set stack pointer


mov [drive_name], dl

mov si, msg ; store message in SI register


call print ; call print on message

mov bx,0x1000			; set ES register for loading kernel at 0x19000
mov es,bx
mov bx, 0x5000

call read ; call read BIOS function

;pusha
mov si,read_succ
call print


;popa

switch_pm:
		
	cli ; clear interrupts
	
	lgdt [descriptor] ; load global descriptor table
	
	mov eax,cr0 ; mov cr0 into eax register
	
	or eax,0x1 ; set first bit of cr0
	
	mov cr0,eax ; store eax back in cr0
	
	
	jmp CSGDT:init_pm
	
	

	
	
%include "boot/readb.asm" ; include reading disk routine
%include "boot/gdt.asm" ; include gdt
%include "boot/printb.asm" ; include print routine
%include "boot/print_hexb.asm"



[bits 32]

; set segment registers

init_pm:

	mov ax, DSGDT
	mov ds,ax
	mov ss,ax
	mov gs,ax
	mov fs,ax
	mov es,ax
	; jump to kernel
	; set up basic paging
	; page directory address at 1MB
	mov eax, 0x10000
	; address of page table 4KB after PD
	mov [eax], dword 0x11000
	; set flags
	or [eax], dword 0b11
	; advance forward 4 bytes (address size)
	mov eax, 0x10004
	; 1023 iterations
	mov ecx, 1022
	; fill up page directory
	fill_page_dir:
		; store NULL address with flags 
		mov [eax], dword 0b10
		; advance forward 4 bytes
		add eax, dword 4
		; loop
		loop fill_page_dir
	
	
	; address of first page table
	mov ebx, 0x11000
	; current address (0-4MB)
	mov eax, 0
	; loop 1024 times
	mov ecx,1023
	; fill page table with entries corresponding to each address multiple of 4KB from 0 to 4MB
	fill_page_table:
		; store page aligned address in PTE
		mov [ebx], eax
		; set flags to present
		or [ebx], dword 0b11
		; increment address by 4KB
		add eax,0x1000
		; increment by 4 to get next page table
		add ebx, dword 4
		; loop
		loop fill_page_table
		
	; set page directory
	mov eax, cr3
	or eax, 0x10000
	mov cr3, eax
	
	; enable paging
	mov eax, cr0
	or eax, 0x80000001
	mov cr0, eax


	
	call 0x15000
	

	; hang
	jmp $

	
	


error_msg:
	 db "Error Reading Disk",0 ; error message
	


msg:
	db "Loading System...", 0xA, 0xD, 0
	
	
read_succ:
		db "Read Successful",0xA,0xD,0
	
	
drive_name:
		db 0
	


; fill up with null bytes
times 510 - ($-$$) db 0 ; fill up 512 bytes for boot sector

; boot signature
dw 0xAA55 ; boot signature






