[bits 32]

global int0
global int1
global int2
global int3
global int4
global int5
global int6
global int7
global int8
global int9
global int10
global int11
global int12
global int13
global int14
global int15
global int16
global int17
global int18
global int19
global int20
global int21
global int22
global int23
global int24
global int25
global int26
global int27
global int28
global int29
global int30
global int31


[extern div_zero_handler]
[extern debug_handler]
[extern nmask_handler]
[extern breakpoint_handler]
[extern overflow_handler]
[extern range_exc_handler]
[extern inv_op_handler]
[extern device_na_handler]
[extern double_fault_handler]
[extern cp_legacy_handler]
[extern inv_tss_handler]
[extern seg_np_handler]
[extern stack_fault_handler]
[extern gpf_handler]
[extern page_fault_handler]
[extern float_err_handler]
[extern align_check_handler]
[extern machine_check_handler]
[extern simd_float_handler]
[extern virtual_handler]
[extern security_handler]
[extern save_context]
[extern get_timer]
[extern restore_context]

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
global irq64
global irq128


[extern schedule]
[extern irq1_handler]
[extern irq2_handler]
[extern irq3_handler]
[extern irq4_handler]
[extern irq5_handler]
[extern irq6_handler]
[extern irq7_handler]
[extern irq8_handler]
[extern irq9_handler]
[extern irq10_handler]
[extern irq11_handler]
[extern irq12_handler]
[extern irq13_handler]
[extern irq14_handler]
[extern irq15_handler]
[extern syscall_handler]
[extern qcall_handler]
[extern print_hex]



global lidt_asm


int0:
	pusha
	call div_zero_handler
	popa
	iret
	
int1:
	pusha
	call debug_handler
	popa
	iret
	
int2:
	pusha
	call nmask_handler
	popa
	iret
	
int3:
	pusha
	call breakpoint_handler
	popa
	iret

int4:
	pusha
	call overflow_handler
	popa
	iret
	
int5:
	pusha
	call range_exc_handler
	popa
	iret
	
int6:
	pusha
	call inv_op_handler
	popa
	iret

int7:
	pusha
	call device_na_handler
	popa
	iret
	
int8:
	call print_hex
	add esp, 4
	
	pusha
	call double_fault_handler
	popa
	iret
	
int9:
	pusha
	call cp_legacy_handler
	popa
	iret
	
int10:
	call print_hex
	add esp,4
	
	pusha
	call inv_tss_handler
	popa
	iret
	
int11:
	call print_hex
	add esp,4
	
	pusha
	call seg_np_handler
	popa
	iret
	
int12:
	call print_hex
	add esp,4
	
	pusha
	call stack_fault_handler
	popa
	iret
	

int13:
	call print_hex
	add esp,4
	
	pusha
	call gpf_handler
	popa
	iret

int14:
	call print_hex
	add esp, 4
	
	push dword [esp]
	call print_hex
	add esp, 4	

	pusha
	call page_fault_handler
	popa
	iret
	

int15:
	iret
	
int16:
	pusha
	call float_err_handler
	popa
	iret

int17:
	call print_hex
	add esp,4
	
	pusha
	call align_check_handler
	popa
	iret
	
int18:
	pusha
	call machine_check_handler
	popa
	iret
	
int19:
	pusha
	call simd_float_handler
	popa
	iret
	
int20:
	pusha
	call virtual_handler
	popa
	iret
	
int21:
	iret
	
int22:
	iret

int23:
	iret

int24:
	iret
	
int25:
	iret

int26:
	iret
	
int27:
	iret
	
int28:
	iret

int29:
	iret
	
int30:
	call print_hex
	add esp,4
	
	pusha
	call security_handler
	popa
	iret
	
int31:
	iret	



irq0: 
	pushad
	
	call get_timer	
	cmp eax, 0	
	popad
	je std 


	pushad
		
	; load new IP
	mov ecx, [esp+32]

	; save ESP
	mov ebx, esp
		
	; switch to user stack
	mov esp, [esp+44]
	mov eax, esp
	; push iret structure
	push dword 0x23
	push eax
	push dword 0x206
	push dword 0x1B
	push ecx
	
	; store new user stack pointer
	mov dword [sp_temp], esp
	; restore kernel stack
	mov esp, ebx	
	
	; pop registers off
	popad

	; save stack pointer
	push dword [sp_temp]
	; save register context
	push esi
	push edi
	push edx
	push ecx
	push ebx
	push eax

	call save_context
	
	add esp,28
	
	; call the scheduler
 	call schedule	
	

	; check if timer has started and go to end if not
	cmp eax, 0
	je std
	
	mov dword [sp_temp], eax
	
	call restore_context
	
	mov edi, [eax+20]
	mov esi, [eax+16]
	mov edx, [eax+12]
	mov ecx, [eax+8]
	mov ebx, [eax+4]
	mov eax, [eax]
	
		
	mov esp, dword [sp_temp]
	
	
		
	std:
		pushad
		mov dx, 0x20
		mov al, 0x20
		out dx, al
		popad
		iret
	

	sp_temp dd 0
	

irq1: 
	pusha
	call irq1_handler
	popa
	iret

irq2:
	pusha
	call irq2_handler
	popa
	iret
	
	
irq3:
	pusha
	call irq3_handler
	popa
	iret
	
irq4:
	pusha
	call irq4_handler
	popa
	iret
irq5:
	pusha
	call irq5_handler
	popa
	iret
irq6:
	pusha
	call irq6_handler
	popa
	iret
	
irq7:
	pusha
	call irq7_handler
	popa
	iret
	
irq8:
	pusha
	call irq8_handler
	popa
	iret
irq9:
	pusha
	call irq9_handler
	popa
	iret
irq10:
	pusha
	call irq10_handler
	popa
	iret
irq11:
	pusha
	call irq11_handler
	popa
	iret

irq12:
	pusha
	call irq12_handler
	popa
	iret
	
irq13:
	pusha
	call irq13_handler
	popa
	iret	
	
irq14:
	pusha
	call irq14_handler
	popa
	iret
	
irq15:
	pusha
	call irq15_handler
	popa
	iret
	
irq64:
	push edx
	push ecx
	push ebx
	push eax
	call qcall_handler
	add esp,16
	iret	


irq128:
	push edx
	push ecx
	push ebx
	push eax
	call syscall_handler
	add esp, 16
	iret



	

lidt_asm:
	mov edx, [esp+4]
	idt_desc:
		dw 2048
		address:
			dd 0x0
	mov [address], edx
		
		
		
	
	lidt [idt_desc]
	sti
	ret
	
	
