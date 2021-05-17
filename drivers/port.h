
// unsigned char for porting byte in (8 bits)

unsigned char inb(unsigned short port_addr) {
	unsigned char byte_in;
	__asm__("in %%dx, %%al" : "=a" (byte_in) : "d" (port_addr));
	return byte_in;
} 



void outb(unsigned char byte_out, unsigned short port_addr) {
	__asm__("out %%al, %%dx" : :"a" (byte_out) , "d" (port_addr));
}


// unsigned short for porting word out (16 bits)
unsigned short inw(unsigned short port_addr) {
	unsigned short word_in;
	__asm__("in %%dx, %%ax" : "=a" (word_in) : "d" (port_addr));
	return word_in;
	
}


void outw(unsigned short word_out, unsigned short port_addr) {
	__asm__("out %%ax, %%dx" : :"a" (word_out) , "d" (port_addr));
}

