
#include "../kernel/print.h"

#ifndef ATA_H
#define ATA_H

#define ATA_CONTROL 0x3F6
#define ATA_DATA 0x1F0
#define ATA_ERROR 0x1F1
#define ATA_SEC_COUNT 0x1F2
#define ATA_LBA_LOW 0x1F3
#define ATA_LBA_MID 0x1F4
#define ATA_LBA_HIGH 0x1F5
#define ATA_DRIVE 0x1F6
#define ATA_COMMAND 0x1F7
#define ATA_STATUS 0x1F7


#define BSY 0x80
#define RDY 0x40
#define DF 0x20
#define SRV 0x10
#define DRQ 0x08
#define CORR 0x04
#define IDX 0x02
#define ERR 0x01


#define MASTER_DRIVE 0xE0
#define SLAVE_DRIVE 0xF0
#define ATA_WRITE 0x30
#define ATA_READ 0x20
#define ATA_IDENTIFY 0xEC
#define ATA_CACHE_FLUSH 0xE7


void ata_wait() {
	
	// 400ns wait

	for(int i = 0; i < 15; i++) {
		inb(ATA_STATUS);
	}
	
}


void check_err() {
	int err = inb(ATA_ERROR);
	int errbit = inb(ATA_STATUS) & ERR;
	
	if(err || errbit) {
		print("ERROR_ATA\n");
		print_hex(err);
	}

}


void soft_reset() {
	uint8_t ctrl = inb(ATA_CONTROL);
	ctrl |= 0x04;
	outb(ctrl, ATA_CONTROL);
	ctrl ^= 0x04;
	outb(ctrl, ATA_CONTROL);
	ata_wait();
}



void ata_identify() {
	outb(0, ATA_SEC_COUNT);
	outb(0, ATA_LBA_LOW);
	outb(0, ATA_LBA_MID);
	outb(0, ATA_LBA_HIGH);
	outb(ATA_IDENTIFY, ATA_COMMAND);
	ata_wait();
	
	int id_data[256];
	
	for(int i = 0; i < 256; i++) {
		id_data[i] = inw(ATA_DATA);
		ata_wait();
	}

	ata_wait();
	check_err();	

}


void ata_poll() {
	uint8_t status = inb(ATA_STATUS);
	while((status & BSY) && !(status & DRQ)) {
		status = inb(ATA_STATUS);
	
	}

}


void ata_write(uint32_t LBA, uint8_t sector_count, uint16_t* data) {
	// poll for BSY and DRQ flags
	ata_poll();
	// select drive
	outb(MASTER_DRIVE | ((LBA & 0x0F000000) >> 24), ATA_DRIVE);
	outb(sector_count, ATA_SEC_COUNT);
	outb(LBA & 0xFF, ATA_LBA_LOW);
	outb((LBA & 0xFF00) >> 8, ATA_LBA_MID);
	outb((LBA & 0xFF0000) >> 16, ATA_LBA_HIGH);
	outb(ATA_WRITE, ATA_COMMAND);
	ata_wait();

	
	for(int i = 0; i < 2048; i++) {
		outw(data[i], ATA_DATA);
	}
	
	
	
	outb(ATA_CACHE_FLUSH, ATA_COMMAND);	
	
	ata_wait();
	check_err();
	soft_reset();
	ata_wait();
	ata_poll();

}



void ata_read(uint32_t LBA, uint8_t sector_count, uint16_t* data) {
	
	// select drive
	outb(MASTER_DRIVE | ((LBA & 0x0F000000) >> 24), ATA_DRIVE);
	// poll for BSY and DRQ flags
	ata_poll();
	outb(sector_count, ATA_SEC_COUNT);
	outb(LBA & 0xFF, ATA_LBA_LOW);
	outb((LBA & 0xFF00) >> 8, ATA_LBA_MID);
	outb((LBA & 0xFF0000) >> 16, ATA_LBA_HIGH);
	outb(ATA_READ, ATA_COMMAND);
	// poll for BSY and DRQ flags
	ata_poll();
	ata_wait();
	
	for(int i = 0; i < 2048; i++) {
		data[i] = (uint16_t)(inw(ATA_DATA));
		ata_wait();
	}
	
	outb(ATA_CACHE_FLUSH, ATA_COMMAND);	
	
	ata_wait();
	check_err();
	soft_reset();
	ata_wait();
	ata_poll();

}

#endif

