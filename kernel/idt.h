#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "print.h"
#include "keyboard.h"
#include "../processes/schedule.h"
#include "../drivers/ata.h"
#include "syscall.h"
#include "../qc/qproc.h"
#include "../drivers/qcsim.h"
#include "../qc/qproc.h"
#include "../general/general.h"

#define PICM_CONTROL 0x20
#define PICS_CONTROL 0xA0
#define PICM_DATA 0x21
#define PICS_DATA 0xA1
#define LISTEN_CMD_PIC 0x11

static char* buff_flush_addr = 0x0;

static int dma_flag = 0;
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
static struct idt_entry IDT[256];


// initialize interrupt descriptor table
void initialize_idt() {
	extern int int0();
	extern int int1();
	extern int int2();
	extern int int3();
	extern int int4();
	extern int int5();
	extern int int6();
	extern int int7();
	extern int int8();
	extern int int9();
	extern int int10();
	extern int int11();
	extern int int12();
	extern int int13();
	extern int int14();
	extern int int15();
	extern int int16();
	extern int int17();
	extern int int18();
	extern int int19();
	extern int int20();
	extern int int21();
	extern int int22();
	extern int int23();
	extern int int24();
	extern int int25();
	extern int int26();
	extern int int27();
	extern int int28();
	extern int int29();
	extern int int30();
	extern int int31();
	
	// manually key in idt entry values (without loop) since 
	// some options are different and also it is easier to toggle them
	// on and off like this
	
	IDT[0].offset_low = (uint32_t)int0 & 0xFFFF;
	IDT[0].offset_high = ((uint32_t)int0 &  0xFFFF0000) >> 16;
	IDT[0].zero = 0;
	IDT[0].selector = 0x08;
	IDT[0].type = 0b10001111;
	
	IDT[1].offset_low = (uint32_t)int1 & 0xFFFF;
	IDT[1].offset_high = ((uint32_t)int1 &  0xFFFF0000) >> 16;
	IDT[1].zero = 0;
	IDT[1].selector = 0x08;
	IDT[1].type = 0b10001111;
	
	IDT[2].offset_low = (uint32_t)int2 & 0xFFFF;
	IDT[2].offset_high = ((uint32_t)int2 &  0xFFFF0000) >> 16;
	IDT[2].zero = 0;
	IDT[2].selector = 0x08;
	IDT[2].type = 0b10001111;
	
	IDT[3].offset_low = (uint32_t)int3 & 0xFFFF;
	IDT[3].offset_high = ((uint32_t)int3 &  0xFFFF0000) >> 16;
	IDT[3].zero = 0;
	IDT[3].selector = 0x08;
	IDT[3].type = 0b10001111;
	
	IDT[4].offset_low = (uint32_t)int4 & 0xFFFF;
	IDT[4].offset_high = ((uint32_t)int4 &  0xFFFF0000) >> 16;
	IDT[4].zero = 0;
	IDT[4].selector = 0x08;
	IDT[4].type = 0b10001111;
	
	IDT[5].offset_low = (uint32_t)int5 & 0xFFFF;
	IDT[5].offset_high = ((uint32_t)int5 &  0xFFFF0000) >> 16;
	IDT[5].zero = 0;
	IDT[5].selector = 0x08;
	IDT[5].type = 0b10001111;
	
	IDT[6].offset_low = (uint32_t)int6 & 0xFFFF;
	IDT[6].offset_high = ((uint32_t)int6 &  0xFFFF0000) >> 16;
	IDT[6].zero = 0;
	IDT[6].selector = 0x08;
	IDT[6].type = 0b10001111;
	
	IDT[7].offset_low = (uint32_t)int7 & 0xFFFF;
	IDT[7].offset_high = ((uint32_t)int7 &  0xFFFF0000) >> 16;
	IDT[7].zero = 0;
	IDT[7].selector = 0x08;
	IDT[7].type = 0b10001111;
	
	IDT[8].offset_low = (uint32_t)int8 & 0xFFFF;
	IDT[8].offset_high = ((uint32_t)int8 &  0xFFFF0000) >> 16;
	IDT[8].zero = 0;
	IDT[8].selector = 0x08;
	IDT[8].type = 0b10001111;
	
	IDT[9].offset_low = (uint32_t)int9 & 0xFFFF;
	IDT[9].offset_high = ((uint32_t)int9 &  0xFFFF0000) >> 16;
	IDT[9].zero = 0;
	IDT[9].selector = 0x08;
	IDT[9].type = 0b10001111;
	
	IDT[10].offset_low = (uint32_t)int10 & 0xFFFF;
	IDT[10].offset_high = ((uint32_t)int10 &  0xFFFF0000) >> 16;
	IDT[10].zero = 0;
	IDT[10].selector = 0x08;
	IDT[10].type = 0b10001111;
	
	IDT[11].offset_low = (uint32_t)int11 & 0xFFFF;
	IDT[11].offset_high = ((uint32_t)int11 &  0xFFFF0000) >> 16;
	IDT[11].zero = 0;
	IDT[11].selector = 0x08;
	IDT[11].type = 0b10001111;
	
	IDT[12].offset_low = (uint32_t)int12 & 0xFFFF;
	IDT[12].offset_high = ((uint32_t)int12 &  0xFFFF0000) >> 16;
	IDT[12].zero = 0;
	IDT[12].selector = 0x08;
	IDT[12].type = 0b10001111;
	
	IDT[13].offset_low = (uint32_t)int13 & 0xFFFF;
	IDT[13].offset_high = ((uint32_t)int13 &  0xFFFF0000) >> 16;
	IDT[13].zero = 0;
	IDT[13].selector = 0x08;
	IDT[13].type = 0b10001111;
	
	IDT[14].offset_low = (uint32_t)int14 & 0xFFFF;
	IDT[14].offset_high = ((uint32_t)int14 &  0xFFFF0000) >> 16;
	IDT[14].zero = 0;
	IDT[14].selector = 0x08;
	IDT[14].type = 0b10001111;
	
	IDT[15].offset_low = (uint32_t)int15 & 0xFFFF;
	IDT[15].offset_high = ((uint32_t)int15 &  0xFFFF0000) >> 16;
	IDT[15].zero = 0;
	IDT[15].selector = 0x08;
	IDT[15].type = 0b10001111;
	
	IDT[16].offset_low = (uint32_t)int16 & 0xFFFF;
	IDT[16].offset_high = ((uint32_t)int16 &  0xFFFF0000) >> 16;
	IDT[16].zero = 0;
	IDT[16].selector = 0x08;
	IDT[16].type = 0b10001111;
	
	
	IDT[17].offset_low = (uint32_t)int17 & 0xFFFF;
	IDT[17].offset_high = ((uint32_t)int17 &  0xFFFF0000) >> 16;
	IDT[17].zero = 0;
	IDT[17].selector = 0x08;
	IDT[17].type = 0b10001111;
	
	IDT[18].offset_low = (uint32_t)int18 & 0xFFFF;
	IDT[18].offset_high = ((uint32_t)int18 &  0xFFFF0000) >> 16;
	IDT[18].zero = 0;
	IDT[18].selector = 0x08;
	IDT[18].type = 0b10001111;
	
	
	IDT[19].offset_low = (uint32_t)int19 & 0xFFFF;
	IDT[19].offset_high = ((uint32_t)int19 &  0xFFFF0000) >> 16;
	IDT[19].zero = 0;
	IDT[19].selector = 0x08;
	IDT[19].type = 0b10001111;
	
	IDT[20].offset_low = (uint32_t)int20 & 0xFFFF;
	IDT[20].offset_high = ((uint32_t)int20 &  0xFFFF0000) >> 16;
	IDT[20].zero = 0;
	IDT[20].selector = 0x08;
	IDT[20].type = 0b10001111;
	
	IDT[21].offset_low = (uint32_t)int21 & 0xFFFF;
	IDT[21].offset_high = ((uint32_t)int21 &  0xFFFF0000) >> 16;
	IDT[21].zero = 0;
	IDT[21].selector = 0x08;
	IDT[21].type = 0b10001111;

	IDT[22].offset_low = (uint32_t)int22 & 0xFFFF;
	IDT[22].offset_high = ((uint32_t)int22 &  0xFFFF0000) >> 16;
	IDT[22].zero = 0;
	IDT[22].selector = 0x08;
	IDT[22].type = 0b10001111;
	
	IDT[23].offset_low = (uint32_t)int23 & 0xFFFF;
	IDT[23].offset_high = ((uint32_t)int23 &  0xFFFF0000) >> 16;
	IDT[23].zero = 0;
	IDT[23].selector = 0x08;
	IDT[23].type = 0b10001111;
	
	IDT[24].offset_low = (uint32_t)int24 & 0xFFFF;
	IDT[24].offset_high = ((uint32_t)int24 &  0xFFFF0000) >> 16;
	IDT[24].zero = 0;
	IDT[24].selector = 0x08;
	IDT[24].type = 0b10001111; 
	
	IDT[25].offset_low = (uint32_t)int25 & 0xFFFF;
	IDT[25].offset_high = ((uint32_t)int25 &  0xFFFF0000) >> 16;
	IDT[25].zero = 0;
	IDT[25].selector = 0x08;
	IDT[25].type = 0b10001111;
	
	IDT[26].offset_low = (uint32_t)int26 & 0xFFFF;
	IDT[26].offset_high = ((uint32_t)int26 &  0xFFFF0000) >> 16;
	IDT[26].zero = 0;
	IDT[26].selector = 0x08;
	IDT[26].type = 0b10001111;
	
	IDT[27].offset_low = (uint32_t)int27 & 0xFFFF;
	IDT[27].offset_high = ((uint32_t)int27 &  0xFFFF0000) >> 16;
	IDT[27].zero = 0;
	IDT[27].selector = 0x08;
	IDT[27].type = 0b10001111;
	
	IDT[28].offset_low = (uint32_t)int28 & 0xFFFF;
	IDT[28].offset_high = ((uint32_t)int28 &  0xFFFF0000) >> 16;
	IDT[28].zero = 0;
	IDT[28].selector = 0x08;
	IDT[28].type = 0b10001111;
	
	IDT[29].offset_low = (uint32_t)int29 & 0xFFFF;
	IDT[29].offset_high = ((uint32_t)int29 &  0xFFFF0000) >> 16;
	IDT[29].zero = 0;
	IDT[29].selector = 0x08;
	IDT[29].type = 0b10001111;
	
	IDT[30].offset_low = (uint32_t)int30 & 0xFFFF;
	IDT[30].offset_high = ((uint32_t)int30 &  0xFFFF0000) >> 16;
	IDT[30].zero = 0;
	IDT[30].selector = 0x08;
	IDT[30].type = 0b10001111;
	
	IDT[31].offset_low = (uint32_t)int31 & 0xFFFF;
	IDT[31].offset_high = ((uint32_t)int31 &  0xFFFF0000) >> 16;
	IDT[31].zero = 0;
	IDT[31].selector = 0x08;
	IDT[31].type = 0b10001111;
	
	
	
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
	// tell slave it is to be connected to IRQ2 of master
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
	
	extern int irq128();
	uint32_t syscall_address = (uint32_t)irq128;
	IDT[128].offset_low = syscall_address & 0x0000FFFF;
	IDT[128].offset_high = syscall_address >> 16;
	IDT[128].selector = 0x08;
	IDT[128].type = 0b11101110;
	
	
	extern int irq64();
	uint32_t qcall_address = (uint32_t)irq64;
	IDT[64].offset_low = qcall_address & 0x0000FFFF;
	IDT[64].offset_high = qcall_address >> 16;
	IDT[64].selector = 0x08;
	IDT[64].type = 0b11101110;


	extern int lidt_asm();
	lidt_asm(IDT);
	

}






uint32_t fetch_vpage();

uint32_t qcall_handler(sys_args qparams) {
	switch(qparams.eax) {
		case 0:
			current_proc->qproc = create_qproc();
			return (uint32_t)(current_proc->qproc->qdata);
			break;


		case 1:;
		       	uint8_t* buff_qdata = (uint8_t*)(qparams.ebx);

			//for(int i = 0; i < 28; i++) print_hex(buff_cdata[i]);

			qc_dma_woffset(buff_qdata,1024, qparams.ecx);
		
			break;

		case 2:
			run_quantum();
			break;
	

		case 3:
			return dma_flag;
			break;
	

		case 4:;
		       dma_flag = 0;
			uint8_t* func_start = (uint8_t*)(qparams.ebx);
			int i = 0;
			int strike = 0;
			while(strike < 2) {
				if(func_start[i] == 0xC0 || func_start[i] == 0xDE) strike++;
				else strike = 0;
				i++;
			
			}
	
			i-=2;
			
			memcpy((uint8_t*)func_start,(uint8_t*)(current_proc->qproc->cdata), i); 
			
			
			break;


		case 5:;
			
			dma_flag = 0;
			uint8_t* buff_cdata = (uint8_t*)(current_proc->qproc->cdata);

			qc_dma_write(buff_cdata, 256);
			break;
			

	
	}

	return 0;

}


uint32_t syscall_handler(sys_args params) {
	uint32_t (*ptr)(sys_args) = (uint32_t (*) (sys_args))(tcodes[params.eax][params.ecx]); 
	(*ptr)(params);

}

void div_zero_handler() {
	print("\nDivision By Zero\n");
	while(1);
}

void debug_handler() {
	print("\nDebug Exception\n");
	while(1);
}

void nmask_handler() {
	print("\nNon-maskable interrupt\n");
	while(1);
}

void breakpoint_handler() {
	print("\nBreakpoint Exception\n");
	while(1);
}

void overflow_handler() {
	print("\nOverflow\n");
	while(1);
}

void range_exc_handler() {
	print("\nBound range exceeded\n");
	while(1);
}

void inv_op_handler() {
	print("\nInvalid Opcode\n");
	while(1);
	
}

void device_na_handler() {
	print("\nDevice Not Available\n");
	while(1);

}


void double_fault_handler() {
	print("\nDouble Fault\n");
	while(1);

}

void cp_legacy_handler() {
	print("\nExternal floating-point chip error\n");
	while(1);
}

void inv_tss_handler() {
	print("\nInvalid TSS\n");
	while(1);

}

void seg_np_handler() {
	print("\nSegment not-present\n");
	while(1);
}

void stack_fault_handler() {
	print("\nStack Segment Fault\n");
	while(1);

}

void gpf_handler() {
	print("\nGeneral Protection Fault!\n");
//	__asm__("jmp 0x7c00");
while(1);
}


void page_fault_handler() {
	print("\nPage Fault!\n");
	
	__asm__("jmp 0x15000");
while(1);
}


void float_err_handler() {
	print("\nFloating-point error\n");
	while(1);
}


void align_check_handler() {
	print("\nAlignment Check Error\n");
	while(1);

}

void machine_check_handler() {
	print("\nMachine Check Error\n");
	while(1);
}

void simd_float_handler() {
	print("\nSIMD floating-point error\n");
	while(1);
}

void virtual_handler() {
	print("\nVirtualization Exception\n");
	while(1);
}

void security_handler() {
	print("\nSecurity Exception\n");
	while(1);

}



void irq1_handler() {
	keyboard_handle();
	outb(0x20,0x20);
	return;
}


void irq2_handler() {
	print("IRQ2");
	outb(0x20,PICM_CONTROL);

}


void irq3_handler() {
	print("IRQ3");
	outb(0x20,PICM_CONTROL);

}


void irq4_handler() {
		print("IRQ4");
	outb(0x20,PICM_CONTROL);

}


void irq5_handler() {
	print("IRQ");
	outb(0x20,PICM_CONTROL);

}

void irq6_handler() {
	print("IRQ");
	outb(0x20,PICM_CONTROL);

}


void irq7_handler() {
	print("IRQ");
	outb(0x20,PICM_CONTROL);
}


void irq8_handler() {
	print("IRQ8");
	outb(0x20, PICS_CONTROL);
	outb(0x20,PICM_CONTROL);
}


void irq9_handler() {
	print("IRQ9");
	outb(0x20, PICS_CONTROL);
	outb(0x20,PICM_CONTROL);
}

void irq10_handler() {
	print("IRQ10");
	outb(0x20, PICS_CONTROL);
	outb(0x20,PICM_CONTROL);
}



void irq11_handler() {
	
	//write_32_addr(0x64, read_32_addr(0x24));
	mmio_write32(mmio_read32(0xFEA00000, 0x24), 0xFEA00000, 0x64);
	dma_flag = 1;

	outb(0x20, PICS_CONTROL);
	outb(0x20,PICM_CONTROL);

}


void irq12_handler() {
	print("IRQ12");
	outb(0x20, PICS_CONTROL);
	outb(0x20,PICM_CONTROL);
}


void irq13_handler() {
	print("IRQ13");
	outb(0x20, PICS_CONTROL);
	outb(0x20,PICM_CONTROL);
}

void irq14_handler() {
	//print("IRQ14");
	outb(0x20, PICS_CONTROL);
	outb(0x20, PICM_CONTROL);

}


void irq15_handler() {

	print("IRQ15");
	outb(0x20, PICS_CONTROL);
	outb(0x20,0x20);

}

#endif



