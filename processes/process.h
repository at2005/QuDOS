
#ifndef PROCESS_H
#define PROCESS_H

#ifndef NULL
#define NULL 0
#endif

#define PROC_RUNNING 2
#define PROC_BLOCKED 1
#define PROC_CREATED 0

#include <stddef.h>
#include "../qc/qproc.h"


//void* kmalloc(size_t bytes_req);

typedef struct pframe_entry {
	uint32_t* addr;
	struct pframe_entry* next_pf;
	struct pframe_entry* prev_pf;
} pframe_entry;


typedef struct iret_stack {
	uint32_t proc_ip;
	uint32_t user_cs;
	uint32_t user_eflags;
	uint32_t proc_stack;
	uint32_t user_ds;
} iret_stack;


// structure to store register states during context switching
typedef struct registers {
	// accumulator
	uint32_t eax;
	
	// base
	uint32_t ebx;
	
	// counter
	uint32_t ecx;
	
	// data 
	uint32_t edx;
	
	// source
	uint32_t esi;
	
	// destination
	uint32_t edi;
} registers;



// structure to store process stack information during context switching
typedef struct stack {
	// stack pointer
	uint32_t esp;
	
	// base pointer
	uint32_t ebp;
} stack;



// Process control block or process table entry
typedef struct process_struct {
	// process identifier (PID)
	uint32_t pid;
	
	// PID of parent
	uint32_t parent_pid;
	
	// can be one of three states, CREATED, BLOCKED, RUNNING
	uint32_t state;
	
	// priority descriptor
	uint32_t priority;
	
	// struct to save registers while context switching 
	registers local_registers;
	
	// struct to store process stack information
	stack local_stack;

//	uint32_t kstack;	
	// program instruction pointer
	uint32_t eip;
	
	// program start address
	uint32_t program_start;
	
	// where to JMP when loading process
	uint32_t code_segment;
	
	qproc_struct* qproc; 

	pframe_entry* pf_list;


	// next process
	struct process_struct* next_proc;
	// previous process
	struct process_struct* prev_proc; 
} process_struct;



static process_struct* proc_head;

// function for process initialization
process_struct* init_proc() {
	// create process table head (double-linked list head)
	proc_head = (process_struct*)kmalloc(sizeof(process_struct));
	// set list head to point to itself
	proc_head->next_proc = proc_head;
	proc_head->prev_proc = proc_head;
	// invalid pointer where stack is 
	proc_head->local_stack.esp = 0xDEADC0DE;
	// invalid pointer where eip is
	proc_head->eip = 0xDEADC0DE;
	// return the process table head
	return proc_head;
}


// function to add process to table
void add_proc(process_struct* new_proc) {
	// set the previous process's next node to new process
	proc_head->prev_proc->next_proc = new_proc;
	// set new process's previous process to currently last process in table
	new_proc->prev_proc = proc_head->prev_proc;
	// set the list head's previous process to new process
	proc_head->prev_proc = new_proc;
	// set new processes's next process to process head
	new_proc->next_proc = proc_head;
	
}

// function to create process
process_struct* create_proc(uint32_t* proc_ip, pframe_entry* pf_ls) {
	// allocate space for a new process structure
	process_struct* new_proc = (process_struct*)kmalloc(sizeof(process_struct));
	// set page frame list
	new_proc->pf_list = pf_ls;
	// set instruction pointer
	new_proc->eip = (uint32_t)proc_ip;
	// set start address
	new_proc->program_start = (uint32_t)proc_ip;
	// add process to process table
	add_proc(new_proc);
	return new_proc;
}

// create page frame list to hold processes' page frames 
pframe_entry* create_pfls() {
	// create list head and allocate space for it
	pframe_entry* pframe_head = (pframe_entry*)(kmalloc(sizeof(pframe_entry)));
	// set head address to invalid pointer
	pframe_head->addr = (uint32_t*)0xDEADC0DE;
	// set head to point to itself
	pframe_head->next_pf = pframe_head;
	pframe_head->prev_pf = pframe_head;
	// return the list head
	return pframe_head;
}


// function to create page frame list entry
void create_pfe(pframe_entry* pf_head, uint32_t* pf_addr) {
	// create and allocate new page frame list entry
	pframe_entry* new_pfe = (pframe_entry*)(kmalloc(sizeof(pframe_entry)));
	// last element to point to new entry
	pf_head->prev_pf->next_pf = new_pfe;
	// prev of new entry to be set to currently last element
	new_pfe->prev_pf = pf_head->prev_pf;
	// head's prev entry to new entry
	pf_head->prev_pf = new_pfe;
	// new entry's next entry to head
	new_pfe->next_pf = pf_head;
	new_pfe->addr = pf_addr;	
}


#endif



