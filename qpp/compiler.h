#include <stddef.h>

#include "parser/SyntaxTree.h"
#include <fstream>

// create global variables
static int jmp_flag = 0;
static int counter = 0;
static int var_counter = 0;
static int within_scope = 0;

std::unordered_map<string,int> symbol_table = {};
// holds the status of each register
static struct  {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;

} free_regs;

// method to check whether reg is free and return if so
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


// free a given register
void free_reg(string reg) {
	if(reg == "eax") free_regs.eax = 0;
	else if(reg == "ebx") free_regs.ebx = 0;
	else if(reg == "ecx") free_regs.ecx = 0;
	else if(reg == "edx") free_regs.edx = 0;
	else if(reg == "edx") free_regs.edx = 0;
	else if(reg == "esi") free_regs.esi = 0;
	else if(reg == "edi") free_regs.edi = 0;
}


// split a 32-bit register into its 16-bit counterpart
string get_word_reg(string reg) {
	if(reg == "eax") return "ax";
	else if(reg == "ebx") return "bx";
	else if(reg == "ecx") return "cx";
	else if(reg == "edx") return "dx";
	else if(reg == "esi") return "si";
	else if(reg == "edi") return "di";
	return "";

}



// split a 32-bit register into its 8-bit counterpart
string get_byte_reg(string reg) {
	if(reg == "ecx") return "cl";
	return "";
}



void write_reg(int a) {}
int lookup() {return 0;}


static ofstream file("./out.asm");

string compile(SyntaxTree* st) {

	Node* root = st->getRoot();
	

	if(root->getTToken() == "OPERATOR") { 
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());

		string lreg = compile(&left_tree);
		string rreg = compile(&right_tree);
		
		string op_type = "";
		if(root->getTValue() == "+") op_type = "add ";
		else if(root->getTValue() == "-") op_type = "sub ";
		else if (root->getTValue() == "*") op_type = "imul ";
		else if(root->getTValue() == "/") op_type = "idiv ";	
		file << op_type  << lreg << "," << rreg << endl;
		free_reg(rreg);
	
		return lreg;
	}


	else if(root->getTToken() == "COMPARISON_OPERATOR") {
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		string lreg = compile(&left_tree);
		string rreg = compile(&right_tree);
		
		file << "cmp " << lreg << "," << rreg << endl;
		
		string cmp_type;

		if(root->getTValue() == ">") {
			if(!jmp_flag) cmp_type = "setg "; 
			else cmp_type = "jle ";
		}
		
		else if(root->getTValue() == ">=") {
			if(!jmp_flag) cmp_type = "setge ";
		       	else cmp_type = "jl ";
		}

		else if(root->getTValue() == "<") {
			if(!jmp_flag) cmp_type = "setl ";
		       	else cmp_type = "jge ";
		}

		else if(root->getTValue() == "<=") {
			if(!jmp_flag) cmp_type = "setle ";
		       	else cmp_type = "jg ";
		}

		else if(root->getTValue() == "==") {
			if(!jmp_flag) cmp_type = "sete ";
		       	else cmp_type = "jne ";
		}

		else if(root->getTValue() == "!=") {
		       	if(!jmp_flag) cmp_type = "setne ";
		       	else cmp_type = "je ";
		}
		
		if(!jmp_flag) {
			string reg = get_free_reg();
			string byte_reg = get_byte_reg(reg);
			file << "and " << reg << "," << "0x0" << endl;	
			file << cmp_type << byte_reg << endl;
			return reg;	
		}
		

		
		string label = "l" + to_string(counter);	
		counter++;
		file << cmp_type << label << endl;
		return label;			
	
	}	


	else if(root->getTToken() == "NUMBER") {
		string val = root->getTValue();
		string free_reg = get_free_reg();
		file << "mov " << free_reg << "," << val << endl;
		return free_reg;
	}		

	else if(root->getTToken() == "IDENTIFIER") {
		cout << var_counter << endl;
		return " dword [esp+" + to_string(4*(var_counter - (symbol_table[root->getTValue()] + 1))) + "]";		
	
	}

	else if(root->getTToken() == "ASSIGNMENT") {

		string var_name = root->getLeftChild()->getTValue();
		symbol_table.insert({var_name, var_counter});
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		string res = compile(&right_tree);
		file << "push " << res << endl;
		free_reg(res);
		var_counter++;
		return res;
	
	}


	else if(root->getTValue() == "if") {
		within_scope++;
		jmp_flag = 1;
		SyntaxTree cond_tree = SyntaxTree(root->getLeftChild());
		string lbl = compile(&cond_tree);
		
		for(int i = 0; i < st->get_child_trees().size(); i++) {
			SyntaxTree* child = &(st->get_child_trees()[i]);
			compile(child);
		
		}
		
		file << lbl  << ":\n";
		
		within_scope--;
		return "";	
			
	}


	else if(root->getTValue() == "printh") {
		file << "call printh\n";
		return "printh";
	}


	file << "jmp $";
	
	file.close();
	return "";
}
