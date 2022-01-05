

#include "print.h"
#include "idt.h"
#include "../processes/process.h"
#include "../memory/paging.h"
#include "../drivers/block.h"
#include "../fsys/fs.h"
#include "../fsys/fmanage.h"
#include "../processes/readelf.h"
#include "../processes/exec.h"
#include "../qc/qproc.h"
#include "../drivers/pci.h"
#include "../drivers/qcsim.h"

extern void enter_user_mode();
extern uint32_t tss_start;
extern void user_func();

void main() {
	init_vidmem();
	// initialize interrupt descriptor table
	initialize_idt();
	// initialize keyboard
	initialize_keyboard();
	// enable keyboard
	//enable_keyboard();
	// map first 12MB to itself
	id_map(0);
	// initialize 4MB of heap for kernel use
	init_kernel_mem();
	// initialize physical memory management structures
	initialize_mem();
	
	
	// allocate 8MB for kernel + heap
	buddy_allocator(0x00800000);
	
	// allocate another 4MB for paging structures
	buddy_allocator(0x00400000);
	int* pd = id_map(1);
	
	// initialize the file system if not already

//	check_bus();	

	init_fs();
	qproc_init();	
	init_syscall();	
	// set up a 12KB buffer
	uint16_t* buff = (uint16_t*)kmalloc(4096*3);
		
	// read executable into buffer
	block_read(8, buff);
	block_read(9, (uint16_t*)((int)buff + 0x1000));
	block_read(10, (uint16_t*)((int)buff + 0x2000));


/*	uint16_t* buff_proc2 = (uint16_t*)kmalloc(4096*3);
	block_read(12,buff_proc2);
	block_read(13, (uint16_t*)((int)buff_proc2 + 0x1000));
	block_read(14, (uint16_t*)((int)buff_proc2 + 0x2000));

*/
	// initialize root process	
	process_struct* rproc = init_proc();
	
	// create a new process after reading from elf file 
	process_struct* new_proc = read_elf((uint8_t*)buff);
	// set up new process stack
	uint32_t* stack_bottom = get_page(); //(uint32_t*)0x09000000;
	map_identity(stack_bottom);

	// map stack to a physical page frame
	kmmap((uint32_t)stack_bottom);
	// set stack to hold iret information
	new_proc->local_stack.esp = ((uint32_t)stack_bottom + 0xFFA) - sizeof(iret_stack);
	// set up initial IRET stack
	iret_stack* pstack_init = (iret_stack*)(new_proc->local_stack.esp);
	
	check_bus();	

	pstack_init->user_ds = 0x23;
	pstack_init->proc_stack = new_proc->local_stack.esp;
	pstack_init->user_eflags = 0x206;
	pstack_init->user_cs = 0x1B;
	pstack_init->proc_ip = new_proc->eip;
	current_proc = new_proc;

//	process_struct* new_proc2 = readelf((uint8_t*)buff_proc2);
	
//	for(int i = 0; i < 10; i++) print_hex(buff_proc2[i]);

	//uint32_t* stack_bottom2 = get_page();
	//map_identity(stack_bottom2);
	
	
	map_identity(0xFEA00000);
	map_identity(0xFEA40000);
	
//	fork(new_proc);

	start_timer = 1;
	enter_user_mode(stack_bottom);

	


}	
