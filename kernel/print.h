#include "../drivers/port.h"
#define VIDEO_MEMORY 0xB8000
#define GREEN_ON_BLACK 0x02
#define BLUE_ON_BLACK 0x03
#define WHITE_ON_BLACK 0x0f
#define CURSOR_PORT_1 0x3D5


// get location offset based on rows and columns
unsigned char* get_location(unsigned int row, unsigned int column) {
	// bit shifts correspond to (row * 80) = (row * 64) + (row * 16)
	int num_bytes = (row << 6) + (row << 4) + column;
	
	// multiply num_bytes by two to account for color bytes and add offset to initial video memory
	int position = VIDEO_MEMORY + (num_bytes << 1);
	return (unsigned char*)position;
	
}


// function to print character
void print_char(unsigned char ch, unsigned int color) {
	// set video memory to character
	*(unsigned char*)VIDEO_MEMORY = ch;
	// set video memory + 1 to color
	*(unsigned char*)(VIDEO_MEMORY+1) = color;
}



// print character at specified row/columns
void print_char_at_loc(unsigned char ch, unsigned int color, unsigned char* position) {
	// write character to position
	*position = ch;
	// write color to next byte
	*(position+1) = color; 
}



// print string at location
void print_string_at_loc(char* string, int color, unsigned char* loc) {
	// declare video memory
	unsigned char* vidmem = (unsigned char*)VIDEO_MEMORY;
	
	// set video memory offset
	if(loc != 0) vidmem = loc; 
	volatile int j = 0;
	
	// iterate over string
	for(int i = 0; string[i] != '\0'; i++) {
		// print character at location
		print_char_at_loc(string[i], color, vidmem);
		// increment location
		vidmem+=2;
	}
}



// print string at default location
void print(char* string, int color) {
	// declare video memory
	unsigned char* vidmem = (unsigned char*)VIDEO_MEMORY;
	// iterate over string
	for(int i = 0; string[i] != '\0'; i++) {
		// print char at location
		print_char_at_loc(string[i], color, vidmem);
		// increment video memory by two
		vidmem+=2;
	}
	
	
}


unsigned char* get_cursor() {
	//outb();		
}



// clear screen function
void clear_screen() {
	unsigned char* vidmem = (unsigned char*)VIDEO_MEMORY;
	volatile int j = 0;
	
	for(int i = 0; i < 80*25; i++) {
		vidmem[j] = ' ';
		vidmem+=2;
	}
	
}

