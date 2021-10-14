#include <stddef.h>

#include "parser/SyntaxTree.h"
#include <fstream>


static int counter = 0;

void inc_lcounter() {
	counter++;
}


static struct  {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;

} free_regs;

string get_free_reg() {
	if(free_regs.eax == 0) {
		free_regs.eax = 1;
		return "eax";
	}

	else if(free_regs.ebx == 0) {
		free_regs.ebx = 1;
	       	return "ebx";
	}
	
	else if(free_regs.ecx == 0) {
		free_regs.ecx = 1;
	       	return "ecx";
	}
	
	else if(free_regs.edx == 0) {
		free_regs.edx = 1;
	       	return "edx";
	}
	
	else if(free_regs.esi == 0) {
		free_regs.esi = 1;
	       	return "esi";
	}
	
	else if(free_regs.edi == 0) {
		free_regs.edi = 1;
	       	return "edi";
	}
	return "NONE_FREE";

}


void free_reg(string reg) {
	if(reg == "eax") free_regs.eax = 0;
	else if(reg == "ebx") free_regs.ebx = 0;
	else if(reg == "ecx") free_regs.ecx = 0;
	else if(reg == "edx") free_regs.edx = 0;
	else if(reg == "edx") free_regs.edx = 0;
	else if(reg == "esi") free_regs.esi = 0;
	else if(reg == "edi") free_regs.edi = 0;
}


string get_word_reg(string reg) {
	if(reg == "ecx") return "cx";


}

string get_byte_reg(string reg) {
	if(reg == "ecx") return "cl";

}


void write_reg(int a) {}
int lookup() {}


static ofstream file("./out.asm");

string compile(SyntaxTree* st) {

	Node* root = st->getRoot();
	if(root->getTToken() == "OPERATOR") { 
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());

		string lreg = compile(&left_tree);
		string rreg = compile(&right_tree);
		
		if(root->getTValue() == "+") file << "add " << lreg << "," << rreg << endl;
		else if(root->getTValue() == "-") file << "sub " << lreg << "," << rreg << endl;
		else if (root->getTValue() == "*") file << "imul " << lreg << "," << rreg << endl;
		
		free_reg(rreg);
	
		return lreg;
	}


	else if(root->getTToken() == "COMPARISON_OPERATOR") {
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		string lreg = compile(&left_tree);
		string rreg = compile(&right_tree);
		
		file << "cmp " << lreg << "," << rreg << endl;
		
		if(root->getTValue() == ">") {
			string reg = get_free_reg();
			string byte_reg = get_byte_reg(reg);
			file << "and " << reg << "," << "0x0" << endl;	
			file << "setg " << byte_reg << endl;
			return reg;
		}		
		
		

	
	}	

	else if(root->getTToken() == "NUMBER") {
		string val = root->getTValue();
		string free_reg = get_free_reg();
		file << "mov " << free_reg << "," << val << endl;
		return free_reg;
	}		

	else if(root->getTToken() == "IDENTIFIER") {
				
	
	}

	else if(root->getTToken() == "ASSIGNMENT") {
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		string res = compile(&right_tree);
		file << "push " << res << endl;
	
	}
	
	file.close();

}
