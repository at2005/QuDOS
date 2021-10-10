
#ifndef READELF_H
#define READELF_H

#include "process.h"

typedef uint32_t elf32_addr;
typedef uint16_t elf32_half;
typedef uint32_t elf32_offset;
typedef int32_t elf32_sword;
typedef uint32_t elf32_word;

#define ELF32_LOAD 0x1
#define ELF_MAGIC0 0x7F
#define ELF_MAGSTR ("ELF\0")


typedef struct elf_header {
	uint8_t elf_id[16];
	elf32_half type;
	elf32_half machine;
	elf32_word version;
	elf32_addr entry;
	elf32_offset prog_head_off;
	elf32_offset sect_head_off;
	elf32_word flags;
	elf32_half ehead_size;
	elf32_half proghte_size;
	elf32_half num_proghte;
	elf32_half secthte_size;
	elf32_half num_secthe;
	elf32_half strtable_index;


} __attribute__((packed)) elf_header;


typedef struct program_header {
	elf32_word p_type;
	elf32_word p_offset;
	elf32_addr p_vaddr;
	elf32_addr p_paddr;
	elf32_word p_filesz;
	elf32_word p_memsz;
	elf32_word p_flags;
	elf32_word p_align;


} __attribute__((packed)) program_header;

process_struct* read_elf(uint8_t* buffer) {
	// read elf header
	elf_header* ehead = (elf_header*)buffer;
	// get first magic byte 0x7F
	uint8_t magic_num = ehead->elf_id[0];
	// get ELF in ASCII
	unsigned char elf_strid[4];
	elf_strid[0] = ehead->elf_id[1];
	elf_strid[1] = ehead->elf_id[2];
	elf_strid[2] = ehead->elf_id[3];
	elf_strid[3] = '\0';
	// compare and check if magic bytes are valid
	bool test_str = strcmp(elf_strid, ELF_MAGSTR);
	if(magic_num != ELF_MAGIC0 || !test_str) {
	       	print("ELF ID FAILED");
	       	return (process_struct*)NULL; 
	}
	
	
	// read program header address
	program_header* phead = (program_header*)((int)buffer + ehead->prog_head_off);
	// create page frame list	
	pframe_entry* proc_pfhead = create_pfls();	
		

	// iterate over each program header
	for(int i = 0; i < ehead->num_proghte; i++) {
		// check if LOAD
		if(phead[i].p_type == ELF32_LOAD) {
			// get virtual address
			elf32_word load_address = phead[i].p_vaddr;
			// calculate number of pages to map	
			uint32_t num_pages = phead[i].p_memsz / 0x1000;
			// if extra memory is required map another page
			if(phead[i].p_memsz % 0x1000 != 0) num_pages++;
		
			// map each virtual page to a physical page frame
			for(int page = 0; page < num_pages; page++) {
				uint32_t page_frame = kmmap(load_address+page*0x1000);
				create_pfe(proc_pfhead, (uint32_t*)(page_frame));

			}

			
			// get start address
			uint8_t* start_address = (uint8_t*)((uint32_t)buffer + phead[i].p_offset);
			// get virtual address
			uint8_t* virtual_addr = (uint8_t*)(phead[i].p_vaddr);
			// copy memory from buffer to virtual address
			memcpy(start_address, virtual_addr, phead[i].p_memsz);	
				

		}
	
	}
	
	// create new process
	process_struct* proc = create_proc((uint32_t*)ehead->entry, proc_pfhead);
	return proc;
		

}	

#endif
