
[bits 16] ; 16 bit mode

[org 0x7c00] ; start executing at 0x7c00

mov bp, 0x9000 ; set up stack
mov sp,bp ; set stack pointer


mov [drive_name], dl

mov si, msg ; store message in SI register


call print ; call print on message


mov bx,0x1000

call read ; call read BIOS function

mov si,read_succ
call print

mov ah,0x06
mov al,0x00
int 0x13

switch_pm:
		
	cli ; clear interrupts
	
	lgdt [descriptor] ; load global descriptor table
	
	mov eax,cr0 ; mov cr0 into eax register
	
	or eax,0x1 ; set first bit of cr0
	
	mov cr0,eax ; store eax back in cr0
	
	
	jmp CSGDT:init_pm
	
	

	
	
%include "readb.asm"



%include "gdt.asm"

%include "printb.asm" ; include print routine



[bits 32]


init_pm:
	mov ax, DSGDT
	mov ds,ax
	mov ss,ax
	mov gs,ax
	mov fs,ax
	mov es,ax
	
	call 0x1000
	jmp $

	
	


error_msg:
	 db "Error Reading Disk",0 ; error message
	


msg:
	db "Loading System...", 0xA, 0xD, 0
	
	
read_succ:
		db "Read Successful",0xA,0xD,0
	
	
drive_name:
		db 0
	


times 510 - ($-$$) db 0 ; fill up 512 bytes for boot sector

dw 0xAA55 ; boot signature







