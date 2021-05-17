#include <stdint.h>
#include "print.h"
#define PICM_CONTROL 0x20
#define PICS_CONTROL 0xA0
#define PICM_DATA 0x21
#define PICS_DATA 0xA1
#define LISTEN_CMD_PIC 0x11


// entry for each IRQ in interrupt descriptor table
struct idt_entry {
	// holds lower 16 bits of irq handler address
	uint16_t offset_low;
	// code segment selector
	uint16_t selector;
	// declare zero byte
	uint8_t zero;
	// type attribute flags
	uint8_t type;
	// holds higher 16 bits of irq handler address
	uint16_t offset_high;

};



// interrupt descriptor table, i.e., array of IDT entries
struct idt_entry IDT[256];


// idt descriptor structure
struct idt_desc {
	// size of IDT
	uint16_t size;
	// address of IDT
	struct idt_entry* address;
} IDT_DESCRIPTOR = {2047, IDT};


// initialize interrupt descriptor table
void initialize_idt() {
	// declare external irq assembly functions
	extern int irq0();
	extern int irq1();
	extern int irq2();
	extern int irq3();
	extern int irq4();
	extern int irq5();
	extern int irq6();
	extern int irq7();
	extern int irq8();
	extern int irq9();
	extern int irq10();
	extern int irq11();
	extern int irq12();
	extern int irq13();
	extern int irq14();
	extern int irq15();

	
	// declare irq handler addresses
	uint32_t irq0_address = (uint32_t)irq0;
	uint32_t irq1_address = (uint32_t)irq1;
	uint32_t irq2_address = (uint32_t)irq2;
	uint32_t irq3_address = (uint32_t)irq3;
	uint32_t irq4_address = (uint32_t)irq4;
	uint32_t irq5_address = (uint32_t)irq5;
	uint32_t irq6_address = (uint32_t)irq6;
	uint32_t irq7_address = (uint32_t)irq7;
	uint32_t irq8_address = (uint32_t)irq8;
	uint32_t irq9_address = (uint32_t)irq9;
	uint32_t irq10_address = (uint32_t)irq10;
	uint32_t irq11_address = (uint32_t)irq11;
	uint32_t irq12_address = (uint32_t)irq12;
	uint32_t irq13_address = (uint32_t)irq13;
	uint32_t irq14_address = (uint32_t)irq14;
	uint32_t irq15_address = (uint32_t)irq15;

	uint32_t arr_of_addresses[16] = {irq0_address, irq1_address, irq2_address, irq3_address, irq4_address, irq5_address,irq6_address, irq7_address, irq8_address, irq9_address, irq10_address, irq11_address, irq12_address, irq13_address, irq14_address, irq15_address};
	// give both PIC controllers initialze commands
	// command to write
	// master PIC
	outb(LISTEN_CMD_PIC, PICM_CONTROL);
	// slave PIC
	outb(LISTEN_CMD_PIC, PICS_CONTROL);
	
	// command to remap master PIC to offset 32
	outb(0x20, PICM_DATA);
	// command to remap slave PIC to offset 40
	outb(0x28, PICS_DATA);
	
	// command to enable cascading
	// telling master that IRQ2 is connected to slave
	outb(0x04, PICM_DATA);
	// tell slave it is to be connected to IRQ2
	outb(0x02,PICS_DATA);
	
	// additional information
	outb(0x01, PICM_DATA);
	outb(0x01, PICS_DATA);
	
	
	// initialize each interrupt entry in IDT
	// start from index 32 of IDT since these are non-CPU interrupts (Interrupt requests)

	for(volatile int i = 0; i < 16; i++) {
		// irq0
		// set offsets
		// mask low word of address and store
		IDT[32+i].offset_low = arr_of_addresses[i] & 0x0000FFFF;
		// shift high word of address
		IDT[32+i].offset_high = arr_of_addresses[i] >> 16;
		// set selector to code segment selector (each entry in GDT is 8 bytes, and CS is second entry therefore 0x08)
		IDT[32+i].selector = 0x08;
		// set zero byte
		IDT[32+i].zero = 0x0;
		// set type attributes
		IDT[32+i].type = 0b10001110;
		
	}
	
	
	extern int lidt_asm();
	lidt_asm(IDT_DESCRIPTOR);
	

}



void irq0_handler() {
	outb(0x20,0x20);
}


void irq1_handler() {
	print("Hello", 0x0F);
	outb(0x20,0x20);
}
void irq2_handler() {
	outb(0x20,0x20);

}

void irq3_handler() {
	outb(0x20,0x20);

}

void irq4_handler() {
	outb(0x20,0x20);

}


void irq5_handler() {
	outb(0x20,0x20);

}

void irq6_handler() {
	outb(0x20,0x20);

}


void irq7_handler() {
	outb(0x20,0x20);
}


void irq8_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);
}


void irq9_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);
}

void irq10_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);
}


void irq11_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);
}

void irq12_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);
}


void irq13_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);
}

void irq14_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);

}


void irq15_handler() {
	outb(0x20, 0xA0);
	outb(0x20,0x20);

}




