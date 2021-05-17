
#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>
#include "../drivers/port.h"
#define VIDEO_MEMORY 0xB8000
#define GREEN_ON_BLACK 0x02
#define BLUE_ON_BLACK 0x03
#define WHITE_ON_BLACK 0x0f
#define CURSOR_CONTROL_REG 0x3D4
#define CURSOR_DATA_REG 0x3D5


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
	void set_cursor(unsigned short offset);
	// declare video memory
	unsigned char* vidmem = (unsigned char*)VIDEO_MEMORY;
	// iterate over string
	for(int i = 0; string[i] != '\0'; i++) {
		// print char at location
		print_char_at_loc(string[i], color, vidmem);
		// increment video memory by two
		vidmem+=2;
	}
	
	int offset = (int)(vidmem - 0xB8000);
	offset >>= 1;
	set_cursor(offset);
	
}

void print_hex(uint32_t hex, int size) {
	
	for(int i = 0; i < 8; i++) {
		char temp = hex & 0x0000000F;

	}
	
	
}


void print_digit(char digit, char color) {

	if(digit == 0x1) {
		print_char('1', color);
	}
	
	else if(digit == 0x2) {
		print_char('2', color);
	}
	
	else if(digit == 0x3) {
		print_char('3', color);
	}
	
	else if(digit == 0x4) {
		print_char('4', color);
	}
	
	else if(digit == 0x5) {
		print_char('5', color);
	}
	
	else if(digit == 0x6) {
		print_char('6', color);
	}
	
	else if(digit == 0x7) {
		print_char('7', color);
	}
	
	else if(digit == 0x8) {
		print_char('8', color);
	}
	
	else if(digit == 0x9) {
		print_char('9', color);
	}
	
	else if(digit == 0xA) {
		print_char('A', color);
	}
	
	else if(digit == 0xB) {
		print_char('B', color);
	}
	
	else if(digit == 0xC) {
		print_char('C', color);
	}
	
	else if(digit == 0xD) {
		print_char('D', color);
	}
	
	else if(digit == 0xE) {
		print_char('E', color);
	}
	
	else if(digit == 0xF) {
		print_char('F', color);
	}


}



// get cursor offset
unsigned int get_cursor() {
	// select register 14
	outb(14, CURSOR_CONTROL_REG);
	// write to register and shift by a byte because this is the high byte
	int offset = inb(CURSOR_DATA_REG) << 8;
	// select register 15
	outb(15, CURSOR_CONTROL_REG);
	// read low byte
	// |= is optimization for += because we are layering the high byte and the low byte into offset
	offset |= inb(CURSOR_DATA_REG);
	// multiply offset by two to get full (char+colour) offset and return
	return offset << 1;		
}


void set_cursor(unsigned short offset) {
	// select register 14
	outb(14,CURSOR_CONTROL_REG);
	// store low byte from offset
	unsigned char low_byte = offset << 8;
	// write low byte to register
	outb(low_byte,CURSOR_DATA_REG);
	// select register 15
	outb(15, CURSOR_CONTROL_REG);
	// store high byte from offset in register
	outb(offset,CURSOR_DATA_REG);
	// set colour	
	*(unsigned char*)(VIDEO_MEMORY+offset*2 + 1) = GREEN_ON_BLACK;
	
}


// clear screen function
void clear_screen() {
	unsigned char* vidmem = (unsigned char*)VIDEO_MEMORY;
	volatile int j = 0;
	
	for(int i = 0; i < get_cursor(); i++) {
		vidmem[j] = ' ';
		vidmem+=2;
	}
	
}

#endif

