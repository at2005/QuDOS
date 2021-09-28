
#ifndef BLOCK_H
#define BLOCK_H

#include "ata.h"

#define BLOCK_SIZE 4096
#define SEC_SIZE 256
#define SEC_COUNT 16

uint32_t lba_from_block(uint32_t block) {
	return ((block*4096) / 512);
}


void block_write(uint32_t block_num, uint16_t* buffer) {
	uint32_t LBA = lba_from_block(block_num);
	ata_write(LBA, SEC_COUNT, buffer);
	soft_reset();
}



void block_read(uint32_t block_num, uint16_t* buffer) {
	uint32_t LBA = lba_from_block(block_num);
	block_num -= 3;
	ata_read(LBA, SEC_COUNT, buffer);
	//soft_reset();
}



#endif



