#ifndef GENERAL_H
#define GENERAL_H
#include "stdbool.h"


int get_num_bits(int a) {
	int total = 0;
	while(a > 0) {
		a /= 2;
		total++;
	}
	
	return total;
}


int pow(int base, int exponent) {
	int total = 1;
	for(int i = 0; i < exponent; i++) {
		total *= base;
	}
	
	return total;
}

void strcpy(char* a, char* b) {
	int i = 0;
	while(a[i] != '\0') {
		b[i] = a[i];
		i++;
	}
	
	b[i] = '\0';

}



bool strcmp(char* a, char* b) {
	int i = 0;
	while(a[i] != '\0' || b[i] != '\0') {
		if(a[i] != b[i]) return 0;	
		i++;
	
	}
	
	return 1;
	
}	
	
	
	




void erase(char* buffer, int size_in_bytes) {
	for(int i = 0; i < size_in_bytes; i++) {
		buffer[i] = '\0';
	
	}

}


void memcpy(uint8_t* a, uint8_t* b, size_t memsize) {
	for(int i = 0; i < memsize; i++) {
		b[i] = a[i];
	}

} 

#endif

