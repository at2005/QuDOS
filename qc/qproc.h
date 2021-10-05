
#ifndef QPROC_H
#define QPROC_H

#include "../memory/dlist.h"

typedef enum QSTATE {ACTIVE, DORMANT} QSTATE;


typedef struct qproc_info {
	uint32_t cpid;
	uint32_t qpid;
	uint8_t* qdata;
	uint32_t qdatasz;
	QSTATE state;
		

} qproc_info;



void qschedule() {
	qproc_info* qc = (qproc_info*)kmalloc(sizeof(qproc_info));
	klist* qlist = create_klist();
	add_klist(qlist,(uint32_t)(qc));
	

}

#endif
