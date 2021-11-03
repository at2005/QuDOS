
#define NUM_CALL_TYPES 8
#define NUM_CALL 8

static uint32_t** tcodes[NUM_CALL_TYPES];


typedef struct sys_args {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;

} sys_args;

void* kmalloc(size_t bytes);

uint32_t screenpr_sysc(sys_args regs) {
	print((char*)(regs.ebx));

}

uint32_t screenprh_sysc(sys_args regs) {
	print_hex(regs.ebx);


}


uint32_t keyen_sysc(sys_args regs) {

	enable_keyboard();
	char_buff = (char*)regs.ebx;
	buff_count= 0;
}

uint32_t keyisen_sysc(sys_args regs) {
	return keyboard_enabled;		
}


void init_syscall() {
	
	for(int i = 0; i < NUM_CALL_TYPES; i++) {
		tcodes[i] = (uint32_t**)kmalloc(sizeof(uint32_t**)*NUM_CALL);
	
	}

	tcodes[1][0] = (uint32_t*)screenpr_sysc;
	tcodes[2][0] = (uint32_t*)screenprh_sysc;
	tcodes[3][0] = (uint32_t*)keyen_sysc;
	tcodes[3][1] = (uint32_t*)keyisen_sysc;

	

}

