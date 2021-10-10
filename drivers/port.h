
#ifndef PORT_H
#define PORT_H

// for porting byte in/out (8 bits)

uint8_t inb(uint16_t port_addr) {
	uint8_t byte_in;
	__asm__("in %%dx, %%al" : "=a" (byte_in) : "d" (port_addr));
	return byte_in;
} 



void outb(uint8_t byte_out, uint16_t port_addr) {
	__asm__("out %%al, %%dx" : :"a" (byte_out) , "d" (port_addr));
}


// for porting word in/out (16 bits)
uint16_t inw(uint16_t port_addr) {
	uint16_t word_in;
	__asm__("in %%dx, %%ax" : "=a" (word_in) : "d" (port_addr));
	return word_in;
	
}


void outw(uint16_t word_out, uint16_t port_addr) {
	__asm__("out %%ax, %%dx" : :"a" (word_out) , "d" (port_addr));
}


// for porting dword in/out (32 bits)
uint32_t ind(uint16_t port_addr) {
	uint32_t dword_in;		
	__asm__("in %%dx, %%eax" : "=a" (dword_in) : "d" (port_addr));
	return dword_in;
}

void outd(uint32_t dword_out, uint16_t port_addr) {

	__asm__("out %%eax, %%dx" : :"a" (dword_out) , "d" (port_addr));

}


#endif
