
#ifndef QPROC_H
#define QPROC_H

#include "../memory/dlist.h"

typedef enum QSTATE {ACTIVE, DORMANT} QSTATE;

uint32_t fetch_vpage();

static klist* qlist;

typedef struct qproc_struct {
	// holds classical pid of parent processes
	uint32_t cpid;
	// holds pid of quantum process
	uint32_t qpid;
	// header for classical data
	uint8_t* cdata_header;
	// size of header
	uint32_t cheadsz;
	// classical data pointer
	uint8_t* cdata;
	// size of classical data
	uint32_t cdatasz;
	// classical data corresponding to quantum instructions
	uint8_t* qdata;
	// size of quantum data
	uint32_t qdatasz;
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
	// set size
	new_qproc->qdatasz = 1;
	// init state
	new_qproc->state = DORMANT;
	// add to doubly linked list
	add_klist(qlist, (uint32_t)new_qproc);
	// return process
	return new_qproc;

}




#endif
