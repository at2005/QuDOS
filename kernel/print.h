
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
#define NULL 0

static unsigned char* print_offset;


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
	*(unsigned char*)print_offset = ch;
	// set video memory + 1 to color
	*(unsigned char*)(print_offset+1) = color;
	print_offset += 2;
	
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
	void set_newline();
	void set_cursor(unsigned short offset);
	// declare video memory
	unsigned char* vidmem = print_offset;
	
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
	
	print_offset = vidmem;
	int offset = (int)(vidmem - VIDEO_MEMORY);
	offset >>= 1;
	set_cursor(offset);
	set_newline();
	
}



// print string at default location
void print(char* string) {
	char color = GREEN_ON_BLACK;
	void set_cursor(unsigned short offset);
	void set_newline();
	// iterate over string
	for(int i = 0; string[i] != '\0'; i++) {
		// print char at location
		if(string[i] == '\n') {set_newline(); continue;}
		print_char_at_loc(string[i], color, print_offset);
		// increment video memory by two
		print_offset += 2;

	}
	
	int offset = (int)(print_offset - 0xB8000);
	offset >>= 1;
	set_cursor(offset);
	
}




char get_digit(char digit) {

	if(digit == 0x0) {
		return '0';
	}

	if(digit == 0x1) {
		return '1';
	}
	
	else if(digit == 0x2) {
		return '2';
	}
	
	else if(digit == 0x3) {
		return '3';
	}
	
	else if(digit == 0x4) {
		return '4';
	}
	
	else if(digit == 0x5) {
		return '5';
	}
	
	else if(digit == 0x6) {
		return '6';
	}
	
	else if(digit == 0x7) {
		return '7';
	}
	
	else if(digit == 0x8) {
		return '8';
	}
	
	else if(digit == 0x9) {
		return '9';
	}
	
	else if(digit == 0xA) {
		return 'A';
	}
	
	else if(digit == 0xB) {
		return 'B';
	}
	
	else if(digit == 0xC) {
		return 'C';
	}
	
	else if(digit == 0xD) {
		return 'D';
	}
	
	else if(digit == 0xE) {
		return 'E';
	}
	
	else if(digit == 0xF) {
		return 'F';
	}
	
	return 0x00;

}


void print_hex(uint32_t hex) {
	unsigned char* vidmem = (unsigned char*)print_offset;
	print_string_at_loc("0x",GREEN_ON_BLACK, vidmem);
	vidmem += 4;
	char buffer[9];
	for(int i = 0; i < 8; i++) {
		volatile char temp = (hex & 0x0000000F);
		buffer[7-i] = get_digit(temp);
		hex >>= 4;
	}
	
	buffer[8] = '\0';
	print_string_at_loc(buffer, GREEN_ON_BLACK, vidmem);
	
}



// get cursor offset
unsigned short get_cursor() {
	// select register 14
	outb(14, CURSOR_CONTROL_REG);
	// write to register and shift by a byte because this is the high byte
	unsigned short offset = inb(CURSOR_DATA_REG) << 8;
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
	// store high byte from offset
	unsigned char high_byte = (offset & 0xFF00) >> 8;
	// write low byte to register
	outb(high_byte,CURSOR_DATA_REG);
	// select register 15
	outb(15, CURSOR_CONTROL_REG);
	// store low byte from offset in register
	outb((offset & 0x00FF),CURSOR_DATA_REG);
	// set colour	
	*(unsigned char*)(VIDEO_MEMORY+offset*2 + 1) = GREEN_ON_BLACK;
}


void advance_cursor() {
	set_cursor((get_cursor()/2) + 1);
}

void decrement_cursor() {
	set_cursor(get_cursor()/2 - 1);
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


void set_newline() {
	int offset = (int)(print_offset - VIDEO_MEMORY);
	offset >>= 1;
	offset /= 80;
	
	print_offset = get_location(offset+1, 0);
	
	int char_offset = (int)(print_offset - VIDEO_MEMORY);
	char_offset/=2;
	set_cursor(char_offset);
	
}

void init_vidmem() {
	print_offset = (char*)(0xB8000);
	clear_screen();
	set_cursor(NULL);

}



#endif


