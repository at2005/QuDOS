
#ifndef FS_H
#define FS_H

#include "../memory/kmalloc.h"
#include "fmanage.h"

static inode* inode_buffer;

void init_fs() {
	// create bitmaps
	inode_bitmap = (bool*)kmalloc(4096);
	data_bitmap = (bool*)kmalloc(4096);
	// create inode region buffer
	inode_buffer = (inode*)kmalloc(4096);
	
	// initialize inodes
	for(int i = 0; i < (4096/sizeof(inode)); i++) {
		inode_buffer[i].kernel_filename = i;
		inode_buffer[i].used = FALSE;
		inode_buffer[i].size = 0;

	}

	
	// set up root inode
	int root_inode = ialloc();
	inode_buffer[root_inode].kernel_filename = 0;
	inode_buffer[root_inode].block = 3;
	inode_buffer[root_inode].is_dir = TRUE;
	inode_buffer[root_inode].used = TRUE;
	inode_buffer[root_inode].size = 1;
	

	
	// create a bin directory
	int bin_inode = ialloc();
	inode_buffer[bin_inode].kernel_filename = 1;
	inode_buffer[bin_inode].block = 6;
	inode_buffer[bin_inode].is_dir = TRUE;
	inode_buffer[bin_inode].used = TRUE;
	inode_buffer[bin_inode].size = 1;
	

	// write inode region to block no. 2
	block_write(2, (uint16_t*)inode_buffer);
	
	// free inode from buffer
	free((int*)inode_buffer);
	
	// set up files/dirs in root folder
	char filename[4] = "bin\0";
	dir_entry* files_in_root = (dir_entry*)kmalloc(4096);
	files_in_root[0].inode_number = bin_inode;
	strcpy(filename, files_in_root[0].user_filename);
	
	// write root's inode entries to disk	
	block_write(3, (uint16_t*)files_in_root);
	
	
	// make sure data in buffer region is zeroed so it can be reused
	erase((char*)(files_in_root), 4096);
	

	
	// write inode bitmap to disk
	block_write(0, (uint16_t*)inode_bitmap);
	// allocate 4 blocks
	balloc();
	balloc();
	balloc();
	balloc();
	
	// write data bitmap to disk	
	block_write(1, (uint16_t*)data_bitmap);	
	
	// free memory
	free((int*)files_in_root);	


}


uint16_t* read_path(char* path) {
	// alloc memory for each directory
	dir_entry* dir_data = (dir_entry*)kmalloc(4096);
	// read root directory
	block_read(3, (uint16_t*)dir_data);
	// filename buffer for each filename/dir in path
	char path_buffer[16];
	erase(path_buffer, 16);
	// initial directory name is root
	char* dir_name = "";
	int i = 0;
	int k = 0;
	while(1) {
		if(path[i] == '/' || path[i] == '\0') {
			int j = 0;
			while(j < 500) {
				if(strcmp(dir_data[j].user_filename, path_buffer)) {
					//block_read(inode_buffer[dir_data[j].inode_number].block, (uint16_t*)dir_data);
					block_read(6, (uint16_t*)dir_data);
					strcpy(dir_data[j].user_filename, dir_name);
					
					break;
				}
				
				j++;
			

			}
			
	 		erase(path_buffer, 16);
	 		
	 		if(path[i] == '\0') break;
	 		
	 		k = 0;

		}
		
		else {
		
		path_buffer[k] = path[i];
		//print_char(path[i], GREEN_ON_BLACK);
		k++;
		//print(path_buffer);

		}

		i++;

		
		
	}

	return (uint16_t*)dir_data;
}

#endif
