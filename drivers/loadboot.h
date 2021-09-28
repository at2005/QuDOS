
void loadboot() {

	uint16_t data_buff[256];
	uint16_t buffer[256];
	int iter = 0;
	for(int curr_offset = 0; curr_offset < 512; curr_offset+=2) {
		//uint16_t inword = (*(uint8_t*)(i+0x7C00) << 8) | *(uint8_t*)(i+0x7C00+1);
		uint16_t inword = *(uint16_t*)(0x7c00+curr_offset);
		//if(inword == 0xaa55) print_hex(inword);
		data_buff[iter] = inword;
		iter++;
	}
	
	
	ata_write(0, 0, data_buff);
	soft_reset();
	
}
