#ifndef INODE_H
#define INODE_H

#include <stdbool.h>


typedef struct inode {
	// low level filename
	uint32_t kernel_filename;
	// block number
	uint32_t block;
	// size in 4K blocks
	uint32_t size;
	// used or not?
	bool used;
	bool is_dir;
	
} inode;


typedef struct dir_entry {
	char user_filename[16];
	int inode_number;
	
} dir_entry;

#endif
