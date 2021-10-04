
#ifndef KMALLOC_H
#define KMALLOC_H

#define MB4 (4194304 - sizeof(dlist_kheap))
#include "dlist.h"


static dlist_kheap kernel_mem_head;

void init_kernel_mem() {
	// create block header at 4MB
	dlist_kheap* initial_block = (dlist_kheap*)(0x00400000);
	// set left/right link of list head to initial block of 4MB
	kernel_mem_head.left_link = initial_block;
	kernel_mem_head.right_link = initial_block;
	// set data of list head to NULL
	kernel_mem_head.size = (int)NULL;
	// set left/right link of initial block to list head
	initial_block->left_link = &kernel_mem_head;
	initial_block->right_link = &kernel_mem_head;
	// size of initial block of memory is little less than 4MB (but we'll call it 4MB for simplicity)
	initial_block->size = MB4;
}



void* kmalloc(size_t bytes_req) {
	// current node in list to list head
	dlist_kheap* current_node = &kernel_mem_head;
	while(1) {
		// move to next node
		current_node = current_node->right_link;
		// if there is no free block then return max possible 32 bit address (as error code)
		if(current_node == &kernel_mem_head) return (int*)0xFFFFFFFF;
		// if the size of mem block is suitable for returning
		if(current_node->size >= bytes_req) {
			// allocate memory for a new mem block in list
			dlist_kheap* address_of_block = (dlist_kheap*)((int)current_node + sizeof(dlist_kheap) + bytes_req);
			// split the block by setting size to remaining bytes
			address_of_block->size = (current_node->size - bytes_req) + sizeof(dlist_kheap);
			// add element
			add_element_kheap(&kernel_mem_head, address_of_block);
			// set the size to bytes required
			current_node->size = bytes_req;
			// remove node from list (it is used)
			remove_element_kheap(current_node);
			current_node->used = TRUE;
			return (int*)((int)current_node+sizeof(dlist_kheap));
		}
	}	
}


void kfree(void* pointer) {
	// get descriptor for memory region
	dlist_kheap* block_desc = (dlist_kheap*)((int)pointer - sizeof(dlist_kheap));
	// get descriptor for next block
	dlist_kheap* ptr_to_next = (dlist_kheap*)((int)pointer + block_desc->size);

	// if next block is free
	if(ptr_to_next->used == FALSE) {
		// remove next block
		remove_element_kheap(ptr_to_next);
		// increase size of current block to cover this block + next
		block_desc->size = block_desc->size + ptr_to_next->size;	
	}
	
	// add block to free list
	add_element_kheap(&kernel_mem_head, block_desc);
	
	
}

#endif


