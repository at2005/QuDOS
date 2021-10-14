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

bool validate_vendor(uint8_t bus, uint8_t device, uint8_t func) {
	uint16_t res = (uint16_t)((pci_read(bus, device, func, 0)) & 0x0000FFFF);
	if(res == 0xFFFF) return FALSE;
	return TRUE;

}


uint8_t get_header(uint8_t bus, uint8_t device) {
	uint8_t header_type = (uint8_t) ((pci_read(bus,device, 0, 0xC) & 0x00FF0000) >> 16);
	return header_type;			
}


uint32_t get_bar(uint8_t bus, uint8_t device, uint8_t func) {
	uint32_t bar = pci_read(bus, device, func, 0x10) >> 2;
	return bar;
	

}


void check_bus() {
	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 32; j++) {
			if(!validate_vendor(i, j, 0)) continue;
			uint8_t header = get_header(i,j);
				
			switch(header) {
				case 0:
					print_hex((pci_read(i,j,0, 0x10) & 0xFFFFFFFC) >> 4);
				
				case 0x80:
					print_hex(pci_read(i,j,0,0x10) >> 2);
					for(int function = 1; function < 8; function++) {
						if(!validate_vendor(i,j, function)) continue;
						print_hex(pci_read(i,j,function, 0x10) >> 2);
					}
				//	print_hex(pci_read(i,j,0, 0x0));	
			}

		}
	
	}


}

