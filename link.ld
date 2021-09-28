

INPUT(
	kernel/lkernel.o
	processes/tss.o
	processes/switch.o
	memory/set_paging.o
	kernel/irq.o
	kernel/kernel.o

);


SECTIONS {

. = 0x15000;

.text : {*(.text)}

.data : {*(.data)}

.bss  : {*(.bss)}




}






