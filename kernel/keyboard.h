#define TRUE 1
#define FALSE 0

static int keyboard_enabled = FALSE;
static int is_shift = FALSE;
static uint32_t buff_count;
static char* char_buff;

// create key-value pair structure
struct key_value {
	// one byte for key
	char key;
	// one byte for value
	char value;
};


// create key-value array. this is the keyboard scancode map to ASCII
struct key_value keyboard_map_array[60];
struct key_value keyboard_shift_map_array[60];



// function to add key-value pair into hash table
void add_hash_table(struct key_value kv, struct key_value* kb_map) {
	// hash function corresponds to modulo by 60
	volatile uint16_t index = kv.key % 60;
	
	// while cell not empty. keep going until we find empty cell
	while((kb_map[index].key)) {
		// increment index
		index++;
	}
	
	// set entry in hash table to key-value pair
	kb_map[index] = kv;

}



// get ASCII character from scancode
void put_alpha(char key) {
	// calculate index
	uint16_t index = key % 60;
	
	struct key_value* kb_map = keyboard_map_array;
	
	if(is_shift) {
		kb_map = keyboard_shift_map_array;
	}
	
	
	// linear probe array if index was offset while hashing. Keep going until we find value corresponding to key
	while(kb_map[index].key != key) {
		// breakpoint is 120. after we wrap around the array and end up where we were we can assume that value does not exist
		if(index > 120) {
			//print_char(keyboard_map_array[index].value,0x02);
			return ;
		}
		
		// increment index
		index++;
		
	}
	
	// get corresponding ASCII character
	unsigned char res = kb_map[index].value;
	
	// print character with color green on black
	print_char(res,GREEN_ON_BLACK);
	
	if(buff_count < 256) {
		char_buff[buff_count] = res;
		buff_count++;
	}

	else buff_count = 0;
	// advance cursor by one
	advance_cursor();

}





void initialize_keyboard() {
	// initialize structures corresponding to keys pressed. The first element is scancode and second is ASCII character
	struct key_value tab_pressed = {0x0F,'	'};
	struct key_value a_pressed = {0x1E, 'a'};
	struct key_value y_pressed = {0x15, 'y'};
	struct key_value u_pressed = {0x16, 'u'};
	struct key_value s_pressed = {0x1F, 's'};
	struct key_value h_pressed = {0x23, 'h'};
	struct key_value q_pressed = {0x10, 'q'};
	struct key_value w_pressed = {0x11, 'w'};
	struct key_value e_pressed = {0x12, 'e'};
	struct key_value r_pressed = {0x13, 'r'};
	struct key_value t_pressed = {0x14, 't'};
	struct key_value i_pressed = {0x17, 'i'};
	struct key_value o_pressed = {0x18, 'o'};
	struct key_value p_pressed = {0x19, 'p'};
	struct key_value d_pressed = {0x20, 'd'};
	struct key_value f_pressed = {0x21, 'f'};
	struct key_value g_pressed = {0x22, 'g'};
	struct key_value j_pressed = {0x24, 'j'};
	struct key_value k_pressed = {0x25, 'k'};
	struct key_value l_pressed = {0x26, 'l'};
	struct key_value sc_pressed = {0x27, ';'};
	struct key_value qt_pressed = {0x28, '\''};
	struct key_value z_pressed = {0x2C, 'z'};
	struct key_value x_pressed = {0x2D, 'x'};	
	struct key_value c_pressed = {0x2E, 'c'};
	struct key_value v_pressed = {0x2F, 'v'};
	struct key_value b_pressed = {0x30, 'b'};
	struct key_value n_pressed = {0x31, 'n'};	
	struct key_value m_pressed = {0x32, 'm'};
	struct key_value comma_pressed = {0x33, ','};
	struct key_value fs_pressed = {0x34, '.'};
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
	struct key_value minus_pressed = {0x0C, '-'};
	struct key_value equal_pressed = {0x0D, '='};
	struct key_value space_pressed = {0x39, ' '};
	struct key_value fslash_pressed = {0x35, '/'};
	
	
	
	// add key-value pairs to hash table	
	add_hash_table(a_pressed, keyboard_map_array);
	add_hash_table(b_pressed, keyboard_map_array);
	add_hash_table(c_pressed, keyboard_map_array);
	add_hash_table(d_pressed, keyboard_map_array);
	add_hash_table(e_pressed, keyboard_map_array);
	add_hash_table(f_pressed, keyboard_map_array);
	add_hash_table(g_pressed, keyboard_map_array);
	add_hash_table(h_pressed, keyboard_map_array);
	add_hash_table(i_pressed, keyboard_map_array);
	add_hash_table(j_pressed, keyboard_map_array);
	add_hash_table(k_pressed, keyboard_map_array);
	add_hash_table(l_pressed, keyboard_map_array);
	add_hash_table(m_pressed, keyboard_map_array);
	add_hash_table(n_pressed, keyboard_map_array);
	add_hash_table(o_pressed, keyboard_map_array);
	add_hash_table(p_pressed, keyboard_map_array);
	add_hash_table(q_pressed, keyboard_map_array);
	add_hash_table(r_pressed, keyboard_map_array);
	add_hash_table(s_pressed, keyboard_map_array);
	add_hash_table(t_pressed, keyboard_map_array);
	add_hash_table(u_pressed, keyboard_map_array);
	add_hash_table(v_pressed, keyboard_map_array);
	add_hash_table(w_pressed, keyboard_map_array);
	add_hash_table(x_pressed, keyboard_map_array);
	add_hash_table(y_pressed, keyboard_map_array);
	add_hash_table(z_pressed, keyboard_map_array);
	add_hash_table(one_pressed, keyboard_map_array);
	add_hash_table(two_pressed, keyboard_map_array);
	add_hash_table(thr_pressed, keyboard_map_array);
	add_hash_table(fr_pressed, keyboard_map_array);
	add_hash_table(fv_pressed, keyboard_map_array);
	add_hash_table(six_pressed, keyboard_map_array);
	add_hash_table(svn_pressed, keyboard_map_array);
	add_hash_table(eight_pressed, keyboard_map_array);
	add_hash_table(nine_pressed, keyboard_map_array);
	add_hash_table(zero_pressed, keyboard_map_array);
	add_hash_table(space_pressed, keyboard_map_array);
	add_hash_table(sc_pressed, keyboard_map_array);
	add_hash_table(qt_pressed, keyboard_map_array);
	add_hash_table(comma_pressed, keyboard_map_array);
	add_hash_table(fs_pressed, keyboard_map_array);
	add_hash_table(minus_pressed, keyboard_map_array);
	add_hash_table(equal_pressed, keyboard_map_array);	
	add_hash_table(fslash_pressed, keyboard_map_array);	
	
	
	struct key_value exclm_pressed = {0x02, '!'};
	struct key_value qm_pressed = {0x35, '?'};	
	struct key_value underscore_pressed = {0x0C, '_'};	
	struct key_value plus_pressed = {0x0D, '+'};	
	struct key_value acap_pressed = {0x1E, 'A'};
	struct key_value ycap_pressed = {0x15, 'Y'};
	struct key_value ucap_pressed = {0x16, 'U'};
	struct key_value scap_pressed = {0x1F, 'S'};
	struct key_value hcap_pressed = {0x23, 'H'};
	struct key_value qcap_pressed = {0x10, 'Q'};
	struct key_value wcap_pressed = {0x11, 'W'};
	struct key_value ecap_pressed = {0x12, 'E'};
	struct key_value rcap_pressed = {0x13, 'R'};
	struct key_value tcap_pressed = {0x14, 'T'};
	struct key_value icap_pressed = {0x17, 'I'};
	struct key_value ocap_pressed = {0x18, 'O'};
	struct key_value pcap_pressed = {0x19, 'P'};
	struct key_value dcap_pressed = {0x20, 'D'};
	struct key_value fcap_pressed = {0x21, 'F'};
	struct key_value gcap_pressed = {0x22, 'G'};
	struct key_value jcap_pressed = {0x24, 'J'};
	struct key_value kcap_pressed = {0x25, 'K'};
	struct key_value lcap_pressed = {0x26, 'L'};
	struct key_value colon_pressed = {0x27, ':'};
	struct key_value dqt_pressed = {0x28, '\"'}; 
	struct key_value zcap_pressed = {0x2C, 'Z'};
	struct key_value xcap_pressed = {0x2D, 'X'};	
	struct key_value ccap_pressed = {0x2E, 'C'};
	struct key_value vcap_pressed = {0x2F, 'V'};
	struct key_value bcap_pressed = {0x30, 'B'};
	struct key_value ncap_pressed = {0x31, 'N'};	
	struct key_value mcap_pressed = {0x32, 'M'};
	struct key_value langle_pressed = {0x33, '<'};
	struct key_value rangle_pressed = {0x34, '>'};
	
	add_hash_table(exclm_pressed, keyboard_shift_map_array);
	add_hash_table(qm_pressed, keyboard_shift_map_array);
	add_hash_table(underscore_pressed, keyboard_shift_map_array);
	add_hash_table(plus_pressed, keyboard_shift_map_array);	
	add_hash_table(acap_pressed, keyboard_shift_map_array);
	add_hash_table(ycap_pressed, keyboard_shift_map_array);
	add_hash_table(ucap_pressed, keyboard_shift_map_array);
	add_hash_table(scap_pressed, keyboard_shift_map_array);
	add_hash_table(hcap_pressed, keyboard_shift_map_array);
	add_hash_table(qcap_pressed, keyboard_shift_map_array);
	add_hash_table(wcap_pressed, keyboard_shift_map_array);
	add_hash_table(ecap_pressed, keyboard_shift_map_array);
	add_hash_table(rcap_pressed, keyboard_shift_map_array);
	add_hash_table(tcap_pressed, keyboard_shift_map_array);
	add_hash_table(icap_pressed, keyboard_shift_map_array);
	add_hash_table(ocap_pressed, keyboard_shift_map_array);
	add_hash_table(pcap_pressed, keyboard_shift_map_array);
	add_hash_table(dcap_pressed, keyboard_shift_map_array);
	add_hash_table(fcap_pressed, keyboard_shift_map_array);
	add_hash_table(gcap_pressed, keyboard_shift_map_array);
	add_hash_table(jcap_pressed, keyboard_shift_map_array);
	add_hash_table(kcap_pressed, keyboard_shift_map_array);
	add_hash_table(lcap_pressed, keyboard_shift_map_array);
	add_hash_table(zcap_pressed, keyboard_shift_map_array);
	add_hash_table(xcap_pressed, keyboard_shift_map_array);
	add_hash_table(ccap_pressed, keyboard_shift_map_array);
	add_hash_table(vcap_pressed, keyboard_shift_map_array);
	add_hash_table(bcap_pressed, keyboard_shift_map_array);
	add_hash_table(ncap_pressed, keyboard_shift_map_array);
	add_hash_table(mcap_pressed, keyboard_shift_map_array);
	add_hash_table(colon_pressed, keyboard_shift_map_array);
	add_hash_table(dqt_pressed, keyboard_shift_map_array);
	add_hash_table(langle_pressed, keyboard_shift_map_array);
	add_hash_table(rangle_pressed, keyboard_shift_map_array);

}


void enable_keyboard() {
	keyboard_enabled = TRUE;
}

void disable_keyboard() {
	keyboard_enabled = FALSE;
}


// keyboard handler
void keyboard_handle() {
	if(keyboard_enabled) {
		// import scancode
		unsigned char scancode = inb(0x60);
		
		// if shift pressed
		if(scancode == 0x2A) {
			// set shift
			is_shift = TRUE;
		}
		
		// if shift released
		if(scancode == 0xAA) {
			// remove shift
			is_shift = FALSE;
		}
		
		
		// if enter key pressed
		if(scancode == 0x1C) {
			// add a newline
			set_newline();
			// print "A>" 
			//print("A>");
			buff_count = 0;
			disable_keyboard();
			return;
		}
		
		// else if scancode is backspace
		else if(scancode == 0x0E) {
			// decrement print offset by 2
			print_offset -= 2;
			buff_count--;
			// set previous cell to NULL
			*print_offset = 0x0;
			char_buff[buff_count] = '\0';
			// decrement cursor by one
			decrement_cursor();
			return;
			
		}
		
		// if neither then convert scancode into ASCII and print
		put_alpha(scancode);

	}
}

