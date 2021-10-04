#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "process.h"
static process_struct* current_proc;
static uint8_t start_timer;


#include "../kernel/print.h"


uint32_t schedule() {
	
	if(start_timer) {
		current_proc = current_proc->next_proc;
		
		if(current_proc->eip == 0xDEADC0DE) current_proc = current_proc->next_proc;

		return current_proc->local_stack.esp;	
	}	
	
	return 0;
}



void save_context(registers regs, uint32_t esp) {
	if(start_timer) {
		current_proc->local_registers = regs;
		current_proc->local_stack.esp = esp;
		pframe_entry* frame_list = current_proc->pf_list;
		pframe_entry* curr_element = frame_list->next_pf;
		
		while(curr_element != frame_list) {
			
//			print_hex(curr_element->addr);

			curr_element = curr_element->next_pf;
		
		}
	
	}

}


registers* restore_context() {

	return &(current_proc->local_registers);


}



int get_timer() {
	return start_timer;
}


#endif
