#ifndef FMANAGE_H
#define FMANAGE_H

#include "inode.h"
#include "../memory/kmalloc.h"


static bool* inode_bitmap;
static bool* data_bitmap;

void flip_bit(bool* bitmap, uint8_t pos) {
	bitmap[pos] = !(bitmap[pos]);
	
}


uint8_t ialloc() {
	for(int i = 0; i < 256; i++) {
		if(inode_bitmap[i] == FALSE) {
			flip_bit(inode_bitmap, i);
			return i;
		}
	}	

}

uint8_t balloc() {
	for(int i = 0; i < 100; i++) {
		if(data_bitmap[i] == FALSE) {
			flip_bit(data_bitmap, i);
			return i;
		}
	}

}


#endif
