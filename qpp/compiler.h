#include <stddef.h>

#include "parser/SyntaxTree.h"
#include <fstream>




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

void write_reg(int a) {}
int lookup() {}

void add_compile(string target, string b) {
	

}


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
		return lreg;
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
