
global set_paging
global disable_paging
global loadpd
global getpd


set_paging:
	mov eax, cr0
	or eax, 0x80000001
	mov cr0, eax
	ret

disable_paging:
	mov eax, cr0
	xor eax, 0x80000001
	mov cr0, eax
	ret
	
loadpd:
	mov eax, cr3
	mov eax, [esp+4]
	mov cr3, eax
	ret

getpd:
	mov eax, cr3
	ret

