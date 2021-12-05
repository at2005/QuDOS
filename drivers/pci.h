#ifndef PCI_H
#define PCI_H

#include "port.h"

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

uint32_t pci_read(uint8_t bus, uint8_t device, uint8_t func, uint8_t offset) {
	// config address is a 32 bit register
	// bit 31 is enable bit
	uint32_t config_addr = 0x80000000;
	// bits 23-16 hold bus number
	config_addr |= (uint32_t)bus << 16;
	// bits 15-11 hold device number
	config_addr |= (uint32_t)device << 11;
       	// bits 10-8 hold function number
	config_addr |= (uint32_t)func << 8;
	// bits 7-0 hold function offset
	config_addr |= (uint32_t)offset & 0xFC;
	
	outd(config_addr, CONFIG_ADDRESS);

	uint32_t res = ind(CONFIG_DATA);
	return res;	
	

}


void pci_write(uint32_t data, uint8_t bus, uint8_t device, uint8_t func, uint8_t offset) {
	// config address is a 32 bit register
	// bit 31 is enable bit
	uint32_t config_addr = 0x80000000;
	// bits 23-16 hold bus number
	config_addr |= (uint32_t)bus << 16;
	// bits 15-11 hold device number
	config_addr |= (uint32_t)device << 11;
       	// bits 10-8 hold function number
	config_addr |= (uint32_t)func << 8;
	// bits 7-0 hold function offset
	config_addr |= (uint32_t)offset & 0xFC;
	
	outd(config_addr, CONFIG_ADDRESS);

	outd(data, CONFIG_DATA);
	

}



bool validate_vendor(uint8_t bus, uint8_t device, uint8_t func) {
	uint16_t res = (uint16_t)((pci_read(bus, device, func, 0)) & 0x0000FFFF);
	if(res == 0xFFFF) return FALSE;
	return TRUE;

}


uint32_t get_bar_size(uint8_t bus, uint8_t device, uint8_t func) {
	uint32_t bar0 = pci_read(bus,device, func,0x10);
	
	outd(0xFFFFFFFF, CONFIG_DATA);

	uint32_t size = ind(CONFIG_DATA);
	size = ~size + 1;
	
	outd(bar0, CONFIG_DATA);
	return size;
	
}


uint8_t get_header(uint8_t bus, uint8_t device) {
	uint8_t header_type = (uint8_t) ((pci_read(bus,device, 0, 0xC) & 0x00FF0000) >> 16);
	return header_type;			
}


uint32_t get_bar(uint8_t bus, uint8_t device, uint8_t func) {
	uint32_t bar = pci_read(bus, device, func, 0x10);
	return bar;
	

}


void check_bus() {
	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 32; j++) {
			if(!validate_vendor(i, j, 0)) continue;
			uint8_t header = get_header(i,j);
			if(pci_read(i,j,0,0) == 0xDEADC0DE) {
				uint32_t status_cmd = pci_read(i,j,0,0x04);
				status_cmd |= 0x4;
				pci_write(status_cmd,i,j,0,0x04);
			
			}			
			
			switch(header) {
				case 0:
						

				case 0x80:
					for(int function = 1; function < 8; function++) {
						if(!validate_vendor(i,j, function)) continue;
					}
			}

		}
	
	}


}


uint32_t mmio_read32(uint32_t base, uint32_t offset) {
	uint32_t* addr = (uint32_t*)(base+offset);
	return *addr;


}

void mmio_write32(uint32_t data, uint32_t base, uint32_t offset) {
	uint32_t* addr = (uint32_t*)(base+offset);
	*addr = data;

}


#endif
