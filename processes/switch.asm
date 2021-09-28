
global cswitch

[extern print_hex]

cswitch:
	; store current kernel esp
	mov ebx, esp
	
	mov esi, [esp+16] 
	; fetch ip
	mov edx, [esp+12]
	; fetch flags
	mov ecx, [esp+8]
	; fetch stack pointer
	mov esp, [esp+4]
	; save stack pointer		
	mov eax, esp
	
	; set up iret stack frame

	; push data segment
	push dword 0x23
	; push stack pointer
	push dword eax
	; push flags
	push dword ecx
	; push code segment
	push dword 0x1B
	; push next instruction to be executed 
	push dword edx
	; return stack
	mov eax, esi
	; revert stack back to kerne stack
	mov esp, ebx
	ret

