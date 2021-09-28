#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef USED 
#define USED FALSE
#endif

#ifndef FREE
#define FREE TRUE
#endif


#include <stdbool.h>

// doubly linked list for physical frame allocation
typedef struct dlist {
	// left link to previous node
	struct dlist* left_link;
	// right link to next node
	struct dlist* right_link;
	// tag tells us if block is free or not
	bool tag;
	// kval holds log2(memory_block_size)
	int kval;
	// holds pointer to physical memory location
	int* ptr;
} dlist;


// doubly linked list for allocating memory on kernel heap
typedef struct dlist_kheap {
	bool used;
	// holds size of memory block
	int size;
	// left link holds ptr to previous node
	struct dlist_kheap* left_link;
	// right link holds ptr to next node
	struct dlist_kheap* right_link;
	
} dlist_kheap;


void create_list(dlist* ptr_to_head, int mem_kval) {
	// set head's link to itself
	ptr_to_head->left_link = ptr_to_head;
	ptr_to_head->right_link = ptr_to_head;
	// set tag to NULL
	ptr_to_head->tag = (int)NULL;
	// set kval to input kval where kval is log2(power_of_two_memory_block)
	ptr_to_head->kval = mem_kval;
}



void add_element(dlist* ptr_to_head, dlist* ptr_to_new) {
	// set left link of new node to last element
	ptr_to_new->left_link = ptr_to_head->left_link;
	// set right link of new node to list head
	ptr_to_new->right_link = ptr_to_head;

	// set last element's right link to point to new node	
	ptr_to_head->left_link->right_link = ptr_to_new;
	// set list head's left link to point to new node
	ptr_to_head->left_link = ptr_to_new;
	
	
}

void add_element_kheap(dlist_kheap* ptr_to_head, dlist_kheap* ptr_to_new) {
	// set left link of new node to last element
	ptr_to_new->left_link = ptr_to_head->left_link;
	// set right link of new node to list head
	ptr_to_new->right_link = ptr_to_head;

	// set last element's right link to point to new node	
	ptr_to_head->left_link->right_link = ptr_to_new;
	// set list head's left link to point to new node
	ptr_to_head->left_link = ptr_to_new;	

}


void remove_element_kheap(dlist_kheap* node_to_remove) {
	node_to_remove->left_link->right_link = node_to_remove->right_link;
	node_to_remove->right_link->left_link = node_to_remove->left_link;

}

bool is_empty(dlist* ptr_to_head) {
	if(ptr_to_head->left_link == ptr_to_head) {
		return TRUE; 
	}
	
	return FALSE;

} 



dlist* remove_element(dlist* ptr_to_head) {
	// get last element from list
	dlist* element = ptr_to_head->right_link;
	// get second last element and set it to new last 
	ptr_to_head->right_link = element->right_link;
	// 
	element->right_link->left_link = ptr_to_head;
	return element;
}


int sizeof_list(dlist* list_head) {
	int total = 0;
	dlist* ptright  = list_head->right_link;
	while(ptright != list_head) {
		ptright = ptright->right_link;
		total++;
	}
	
	return total;
} 

