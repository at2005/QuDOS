#include <stddef.h>
#include <stdint.h>

extern void printf(char* in);
extern void printh(int a);
extern void scanf(char* buffer);
extern uint32_t quant();

void flush(char* buffer) {

	for(int i = 0; i < 256; i++) buffer[i] = '\0';

}

int main() {
	printf("QOS Developed By Ayush Tambde (2021)\n\n");
	char buffer[256];
	flush(buffer);
		
	while(1) {
	//	printh(quant());	
		printf("A> ");
		scanf(buffer);
		if(buffer[0] == 'h' && buffer[1] == 'i') printf("hello to you too!");
		else printf(buffer);	
		printf("\n");
		flush(buffer);	
	}
	
	
	
	//uint8_t* buffer = (uint8_t*)quant();
		


	return 0;
}


