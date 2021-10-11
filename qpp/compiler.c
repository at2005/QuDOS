#include <stddef.h>

static struct free_regs {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;

};

char* get_free_reg() {
	if(free_regs.eax == 0) return "eax";
	else if(free_regs.ebx == 0) return "ebx";
	else if(free_regs.ecx == 0) return "ecx";
	else if(free_regs.edx == 0) return "edx";
	else if(free_regs.esi == 0) return "esi";
	else if(free_regs.edi == 0) return "edi";
	return "NONE_FREE";

}


void compile(SyntaxTree* st) {
	if(st->getRoot()->getTToken() == "NUMBER") {
		
	
	}	

}
