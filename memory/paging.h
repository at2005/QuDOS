#include "physmem.h"
#include "../kernel/print.h"
extern int loadpd(int* dir_addr);


int* get_pt() {
	int* ptr_to_pt = get_page();
	
	for(int i = 0; i < 1024; i++) {
		ptr_to_pt[i] = (uint32_t)get_page() | 3; 
	}
	
	return ptr_to_pt;
}

        

void set_page_dir() {
	int* pd = get_page();
	pd[0] = (uint32_t)get_pt() | 3;
	print_hex(pd[0]);
	for(int i = 1; i < 1024; i++) {
		
		pd[i] = (uint32_t)get_page() | 2;

	}
	
	
	loadpd(pd);
}


	

int* id_map(int flag) {
	
	// page directory address
	static int pdint __attribute__((aligned(4096)));
	// first page table maps 4KB
	
	static int ptint4MB[1] __attribute__((aligned(4096)));	
	static int ptint8MB[1] __attribute__((aligned(4096)));
	static int ptint12MB[1] __attribute__((aligned(4096)));
	static int pdintreal[1] __attribute__((aligned(4096)));
	//static int ptint16MB[1] __attribute__((aligned(4096)));

	
	//while(1);


	int* pd;
	int* pt4MB;
	int* pt8MB;
	int* pt12MB;
	//int* pt16MB;
	
	if(flag) {
		pd = get_pts_page();
		pt4MB = get_pts_page();
		pt8MB = get_pts_page();
		pt12MB = get_pts_page();
	//	pt16MB= get_pts_page();
	
	}
	
	// address of above addresses
	else {
		pt4MB = (int*)ptint4MB;
		pt8MB = (int*)ptint8MB;
		pt12MB = (int*)ptint12MB;
		//pt16MB = (int*)ptint16MB;
		pd = (int*)pdintreal;
	}
	
	pd[0] = (uint32_t)pt4MB | 3;
	pd[1] = (uint32_t)pt8MB | 3;
	pd[2] = (uint32_t)pt12MB | 3;
	//pd[3] = (uint32_t)pt16MB | 7;
	
	
	for(int i = 4; i < 1024; i++) {
		pd[i] = (uint32_t)2;

	}
	
	
	
	for(int i = 0; i < 1024; i++) {
		//pt16MB[i] = (0x1000 * (i+3072)) | 7;
		pt12MB[i] = (0x00001000 * (i+2048)) | 3;
		pt8MB[i] = (0x00001000 * (i+1024)) | 3;
		pt4MB[i] = (0x00001000 * i) | 3;


	}
		
	
	loadpd(pd);
	
	return pd;

}







