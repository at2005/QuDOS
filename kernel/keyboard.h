
struct key_value {
	char key;
	char value;
};


struct key_value keyboard_map_array[36];


void add_hash_table(struct key_value kv) {
	volatile uint16_t index = kv.key % 36;
	
	while((keyboard_map_array[index].key)) {
		index++;
	}
	
	
	keyboard_map_array[index] = kv;

}



void get_alpha(char key) {
	uint16_t index = key % 36;

	while(keyboard_map_array[index].key != key) {
		if(index > 70) {
			//print_char(keyboard_map_array[index].value,0x02);
			return ;
		}
		
		index++;
		
	}
	
	unsigned char res = keyboard_map_array[index].value;
	
	print_char(res,0x02);
	advance_cursor();
	
}





void initialize_keyboard() {
	struct key_value a_pressed = {0x1E, 'A'};
	struct key_value y_pressed = {0x15, 'Y'};
	struct key_value u_pressed = {0x16, 'U'};
	struct key_value s_pressed = {0x1F, 'S'};
	struct key_value h_pressed = {0x23, 'H'};
	struct key_value q_pressed = {0x10, 'Q'};
	struct key_value w_pressed = {0x11, 'W'};
	struct key_value e_pressed = {0x12, 'E'};
	struct key_value r_pressed = {0x13, 'R'};
	struct key_value t_pressed = {0x14, 'T'};
	struct key_value i_pressed = {0x17, 'I'};
	struct key_value o_pressed = {0x18, 'O'};
	struct key_value p_pressed = {0x19, 'P'};
	struct key_value d_pressed = {0x20, 'D'};
	struct key_value f_pressed = {0x21, 'F'};
	struct key_value g_pressed = {0x22, 'G'};
	struct key_value j_pressed = {0x24, 'J'};
	struct key_value k_pressed = {0x25, 'K'};
	struct key_value l_pressed = {0x26, 'L'};
	struct key_value z_pressed = {0x2C, 'Z'};
	struct key_value x_pressed = {0x2D, 'X'};	
	struct key_value c_pressed = {0x2E, 'C'};
	struct key_value v_pressed = {0x2F, 'V'};
	struct key_value b_pressed = {0x30, 'B'};
	struct key_value n_pressed = {0x31, 'N'};	
	struct key_value m_pressed = {0x32, 'M'};
	struct key_value zero_pressed = {0x0B, '0'};
	struct key_value one_pressed = {0x02, '1'};
	struct key_value two_pressed = {0x03, '2'};
	struct key_value thr_pressed = {0x04, '3'};
	struct key_value fr_pressed = {0x05, '4'};
	struct key_value fv_pressed = {0x06, '5'};
	struct key_value six_pressed = {0x07, '6'};
	struct key_value svn_pressed = {0x08, '7'};
	struct key_value eight_pressed = {0x09, '8'};
	struct key_value nine_pressed = {0x0A, '9'};

	struct key_value space_pressed = {0x39, ' '};

	
	
	add_hash_table(a_pressed);
	add_hash_table(b_pressed);
	add_hash_table(c_pressed);
	add_hash_table(d_pressed);
	add_hash_table(e_pressed);
	add_hash_table(f_pressed);
	add_hash_table(g_pressed);
	add_hash_table(h_pressed);
	add_hash_table(i_pressed);
	add_hash_table(j_pressed);
	add_hash_table(k_pressed);
	add_hash_table(l_pressed);
	add_hash_table(m_pressed);
	add_hash_table(n_pressed);
	add_hash_table(o_pressed);
	add_hash_table(p_pressed);
	add_hash_table(q_pressed);
	add_hash_table(r_pressed);
	add_hash_table(s_pressed);
	add_hash_table(t_pressed);
	add_hash_table(u_pressed);
	add_hash_table(v_pressed);
	add_hash_table(w_pressed);
	add_hash_table(x_pressed);
	add_hash_table(y_pressed);
	add_hash_table(z_pressed);
	add_hash_table(one_pressed);
	add_hash_table(two_pressed);
	add_hash_table(thr_pressed);
	add_hash_table(fr_pressed);
	add_hash_table(fv_pressed);
	add_hash_table(six_pressed);
	add_hash_table(svn_pressed);
	add_hash_table(eight_pressed);
	add_hash_table(nine_pressed);
	add_hash_table(zero_pressed);
	add_hash_table(space_pressed);
	
	
}


void keyboard_handle() {
	unsigned char scancode = inb(0x60);
	//print_hex((uint32_t)scancode);
	if(scancode == 0x1C) {
		set_newline();
		print("A>", 0x02);
		return;
	}
	
	
	else if(scancode == 0x0E) {
		print_offset -= 2;
		*print_offset = 0x0;
		decrement_cursor();
		
	}
	
	get_alpha(scancode);
}
