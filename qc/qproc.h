
#ifndef QPROC_H
#define QPROC_H

#include "../memory/dlist.h"

typedef enum QSTATE {ACTIVE, DORMANT} QSTATE;

uint32_t fetch_vpage();

static klist* qlist;

typedef struct qproc_struct {
	uint32_t cpid;
	uint32_t qpid;
	uint8_t* qdata;
	uint32_t qdatasz;
	QSTATE state;
		

} qproc_struct;




klist* qproc_init() {
	qlist = create_klist();
	return qlist;	

}

qproc_struct* create_qproc() {
	qproc_struct* new_qproc  = (qproc_struct*)kmalloc(sizeof(qproc_struct));
	new_qproc->qdata = (uint8_t*)fetch_vpage();
	new_qproc->qdatasz = 1;
	*(new_qproc->qdata) = 2;
	new_qproc->state = DORMANT;
	add_klist(qlist, (uint32_t)new_qproc);
	return new_qproc;

}




#endif
