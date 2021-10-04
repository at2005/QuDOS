#ifndef EXEC_H
#define EXEC_H

// fork process
uint32_t fork(process_struct* proc) {
	// create new process struct
	process_struct clone;
	// copy all information to new child proc
	clone = *(proc);
	// create new page frame list for new proc
	pframe_entry* new_pfhead = create_pfls();
	clone.pf_list = new_pfhead;
	
	uint8_t* page_buff = (uint8_t*)kmalloc(4096);
	int i = 0;
	// iterate over each page frame in current proc 
	pframe_entry* curr_pf = proc->pf_list->next_pf;
	
	while(curr_pf != proc->pf_list) {
		// create new page frame entry for new proc
		uint32_t page_to_cpy = 0x08048000 + (i*0x1000);

		memcpy((uint8_t*)(page_to_cpy), page_buff, 4096); 
		
		create_pfe(new_pfhead, (uint32_t*)(map_page(page_to_cpy)));

		// advance to next element
		curr_pf = curr_pf->next_pf;
		i++;
	
	}	


}


#endif
