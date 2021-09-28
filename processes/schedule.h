#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "process.h"
static process_struct* current_proc;
static uint8_t start_timer;


#include "../kernel/print.h"


extern uint32_t cswitch();



uint32_t schedule(registers regs) {
	
	if(start_timer) {
		// save registers
		current_proc->local_registers.eax = regs.eax;
		current_proc->local_registers.ebx = regs.ebx;
		current_proc->local_registers.ecx = regs.ecx;
		current_proc->local_registers.edx = regs.edx;
		current_proc->local_registers.esi = regs.esi;
		current_proc->local_registers.edi = regs.edi;
		
		current_proc = current_proc->next_proc;
		
		if(current_proc->eip == 0xDEADC0DE) current_proc = current_proc->next_proc;

	//	return cswitch(stack_ptr,flags, ip);
		return current_proc->local_stack.esp;	
	}	
	
	return 0;
}


void save_stack(uint32_t esp) {

	if(start_timer) {
		current_proc->local_stack.esp = esp;
	}	

}

int get_timer() {
	return start_timer;
}


#endif
