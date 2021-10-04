#include <stddef.h>
#include "../general/general.h"
#include "kmalloc.h"

#define SIZE_OF_MEM 20

#ifndef PHYSMEM_H
#define PHYSMEM_H

extern uint32_t* getpd();

// list headers for each power of two memory block
static dlist k_mems[SIZE_OF_MEM];
static dlist page_struct_mems[11];

int pow(int base, int exponent);

void initialize_mem() {
	for(int i = 0; i < SIZE_OF_MEM; i++) {
		create_list(&(k_mems[i]),i);
	}
	
	for(int i = 0; i < 11; i++) {
		create_list(&(page_struct_mems[i]), i);
	
	}
	
	// get pointer to where we wish to store the first block
	dlist* ptr_to_root = (dlist*)kmalloc(sizeof(dlist));
	
	// get pointer to where we want to store the first block for our page struct (PTS) memory
	dlist* ptr_to_ptmem_root = (dlist*)kmalloc(sizeof(dlist));
	
	// set tag 2GB block to FREE
	ptr_to_root->tag = FREE;
	
	// set 4MB PTS memory to free
	ptr_to_ptmem_root->tag = FREE;
	
	// physical memory begins at 0x00000000
	ptr_to_root->ptr = (int*)0;
	
	// PTS memory begins at 8MB mark
	ptr_to_ptmem_root->ptr = (int*)0x00800000;
	
	// set the kval of our physical memory block to 31 since 2^31 is 2GB
	ptr_to_root->kval = 31;
	
	// set kval of our PTS memory block to 22 since it is 4MB 
	ptr_to_ptmem_root->kval = 22;
	
	// add our blocks to the free list
	add_element(&k_mems[SIZE_OF_MEM-1], ptr_to_root);
	
	add_element(&page_struct_mems[10], ptr_to_ptmem_root);
}


uint32_t* split_block(int index, int k_val, dlist* block, int flag) {
	// check if block is of desired size
	if(index == k_val) {
		block->tag = USED;
		return block->ptr;
	}
			
			
	// else if size is smaller
	// then split, ie divide by two (reduce power by one)
	int j = index - 1;
	// find starting point of free block
	uint32_t* free_block = (uint32_t*)((uint32_t)block->ptr + pow(2,j));
	
	// allocate memory to store header
	dlist* loc_fblk_header = (dlist*)kmalloc(sizeof(dlist));
	
	// set free block's kval to j
	loc_fblk_header->kval = j;
	// set free block's tag to free
	loc_fblk_header->tag = FREE;
	loc_fblk_header->ptr = free_block;
	
	//  flag controls whether we are writing to physical memory or kernel page table memory
	if(flag) {
		// add free block to available memory list
		add_element(&k_mems[j-12], loc_fblk_header); 
	}
	
	else {
		// add block to page table memory list
		add_element(&page_struct_mems[j-12], loc_fblk_header);	
	}
	
	block->tag = USED;
	block->kval = j;
	
	return split_block(j, k_val, block, flag);

}



uint32_t* buddy_allocator(size_t mem_req) {
	// get number of bits = log2(mem_req)					
	int k = get_num_bits(mem_req) - 1;
	// iterate from k to max mem
	for(int i = k; i < 32; i++) {
		volatile int true_index = i - 12;
		// check if list is empty
		if(!is_empty(&k_mems[true_index])) {
			dlist* block = remove_element(&k_mems[true_index]);
			return split_block(i,k,block, 1);
			
		}
	}

}



uint32_t* get_pts_page() {
	// iterate from 4KB to 4MB
	for(int i = 12; i <= 22; i++) {
		// if the memory required is not empty
		if(!is_empty(&page_struct_mems[i-12])) {
			// remove the block from the free list
			dlist* block = remove_element(&page_struct_mems[i-12]);
			// split the block recursively
			return split_block(i, 12, block, 0);	
		}
		
	}

}

uint32_t* get_page() {
	return buddy_allocator(4096);
}


uint32_t get_pde(uint32_t addr) {
	// page directory is the first 12 bits divided by 4. Adjusted, this becomes a shift of 22
	uint32_t page_dir = (addr & 0xFFF00000) >> 22;
	return page_dir;	
}

uint32_t get_ptoffset(uint32_t addr) {
	uint32_t start_pt = addr & 0xFFC00000;
	addr -= start_pt;
	return (addr >> 12);	
}


uint32_t map_page(uint32_t addr) {
	uint32_t* page_dir = getpd();
	// get page dir offset and page table offset
	uint32_t pd_offset = get_pde(addr);
	uint32_t pt_offset = get_ptoffset(addr);
	// check if PDE mapped present
	if(page_dir[pd_offset] == 0x2) {
		// if not then map	
		uint32_t* pt_addr = get_pts_page();
		page_dir[pd_offset] = (uint32_t)pt_addr | 7;
	
	}
	
	// get address of page table
	uint32_t* page_table = (uint32_t*)(page_dir[pd_offset] & 0xFFFFF000);
	// map address to new physical page frame
	
	uint32_t page_frame = (uint32_t)get_page();
	page_table[pt_offset] = (uint32_t)page_frame | 7;
	
	return page_frame;

}



#endif


