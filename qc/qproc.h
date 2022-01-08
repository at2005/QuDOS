
#ifndef QPROC_H
#define QPROC_H

#include "../memory/dlist.h"

typedef enum QSTATE {ACTIVE, DORMANT} QSTATE;

uint32_t fetch_vpage();

static klist* qlist;

typedef struct func_header {
	char id[5];
	uint32_t offset;
	uint32_t num_func;


} func_header;


typedef struct func_table {
	char fname[32];
	uint32_t offset;
	uint32_t size;
	uint32_t addr;	


} func_table;


typedef struct qproc_struct {
	// holds classical pid of parent processes
	uint32_t cpid;
	// holds pid of quantum process
	uint32_t qpid;
	// classical data pointer
	uint8_t* cdata;
	// cdata offset
	uint32_t coffset;
	klist* cfunc_list;
	// classical data corresponding to quantum instructions
	uint8_t* qdata;
	// async func
	uint32_t async_func;
	// current state
	QSTATE state;
		

} qproc_struct;




klist* qproc_init() {
	qlist = create_klist();
	return qlist;	

}

qproc_struct* create_qproc() {
	// create new proc and allocate space for it
	qproc_struct* new_qproc  = (qproc_struct*)kmalloc(sizeof(qproc_struct));
	// allocate/fetch page for quantum data
	new_qproc->cdata = (uint8_t*)fetch_vpage();
	new_qproc->qdata = (uint8_t*)fetch_vpage();
	new_qproc->coffset = sizeof(func_header);
	// init state
	new_qproc->state = DORMANT;
	new_qproc->cfunc_list = create_klist();
	new_qproc->async_func = 0;
	// add to doubly linked list
	add_klist(qlist, (uint32_t)new_qproc);
	// return process
	return new_qproc;

}




#endif
