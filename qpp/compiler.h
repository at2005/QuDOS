#include <stddef.h>

#include "parser/SyntaxTree.h"
#include <fstream>

#define ADD_X86 "add "
#define SUB_X86 "sub "
#define MUL_X86 "imul "
#define DIV_X86 "div "


// create global variables
static int jmp_flag = 0;
static int counter = 0;
static int var_counter = 0;
static int string_counter = 0;
static int within_scope = 0;

string data_section = "section .data:\n";

// structure for symbol table
typedef struct symtab {
	// hash table for variable names -> position 
	std::unordered_map<string, int> table;
	// pointer to a parent symbol table
	struct symtab* parent_table; 

} symtab;


// recursive search the symbol table
int search_symtab(symtab* tab, string var_name) {
	if(tab->table.find(var_name) != tab->table.end()) {
		return tab->table.find(var_name)->second;

	}

	return search_symtab(tab->parent_table, var_name);
	
}


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
	if(reg == "eax") return "al";
	else if(reg == "ebx") return "bl";
	else if(reg == "ecx") return "cl";
	else if(reg == "edx") return "dl";
	return "";
}


static ofstream file("./out.asm");

void mov_x86(string l_op, string r_op) {
	file << "mov " << l_op  << "," << r_op << endl;

}


// compiler function
string compile(SyntaxTree* st, symtab* symbol_table ) {
	// get root node of tree
	Node* root = st->getRoot();
		
	// check if root is an operator
	if(root->getTToken() == "OPERATOR") {
	       // generate syntax trees for left and right children
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());

		// call compiler recursively on each syntax tree
		string lreg = compile(&left_tree, symbol_table);
		string rreg = compile(&right_tree, symbol_table);
		
		// if the left child is an identifier
		if(root->getLeftChild()->getTToken() == "IDENTIFIER") {
			// get a free register
			string temp_reg = get_free_reg();
			// mov the left operand into a register for processing
			mov_x86(temp_reg, lreg);
			// set the left value to the register
			lreg = temp_reg;

		}

		

		// set operation type to instruction
		string op_type = "";
		if(root->getTValue() == "+") op_type = ADD_X86;
		else if(root->getTValue() == "-") op_type = SUB_X86;
		else if (root->getTValue() == "*") op_type = MUL_X86;
		else if(root->getTValue() == "/") op_type = DIV_X86;	
		file << op_type  << lreg << "," << rreg << endl;
		
		free_reg(lreg);
		free_reg(rreg);
		
	
		return lreg;
	}


	else if(root->getTToken() == "COMPARISON_OPERATOR") {
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());

		string lreg = compile(&left_tree, symbol_table);
		string rreg = compile(&right_tree, symbol_table);
		
		if(root->getRightChild()->getTToken() == "IDENTIFIER") {
			string reg = get_free_reg();
			file << "mov " << reg << "," << rreg << endl;
			rreg = reg;
		
		}

		
		file << "cmp " << lreg << "," << rreg << endl;
		
		if(root->getRightChild()->getTToken() == "IDENTIFIER") free_reg(rreg);


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
		int pos = search_symtab(symbol_table, root->getTValue());
		return " dword [esp+" + to_string(4*(var_counter - (pos + 1))) + "]";		
	
	}

	else if(root->getTToken() == "STRING") {
		string str_label =  "s" + to_string(string_counter); 
		data_section +=  str_label + " db \"";
		string str_value = root->getTValue();
	       	for(int i = 0; i < str_value.size(); i++) {
			if(str_value[i] == '\\') {
				data_section += "\",0xA,\"";
				i++;
			}
		
			
			else {	
				data_section += str_value[i];

			
			}

		}
	       
		string_counter++;
		data_section += "\",0\n";
		return str_label;
		
	}

	else if(root->getTToken() == "ASSIGNMENT") {
		string var_name = root->getLeftChild()->getTValue();
		symbol_table->table.insert({var_name, var_counter});
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		string res = compile(&right_tree, symbol_table);
		file << "push " << res << endl;
		free_reg(res);
		var_counter++;
		return res;
	
	}


	else if(root->getTValue() == "if") {
		within_scope++;
		symtab* scope_table = new symtab;
		scope_table->table = {};
		jmp_flag = 1;
		SyntaxTree cond_tree = SyntaxTree(root->getLeftChild());
		string lbl = compile(&cond_tree, symbol_table);	
		
		for(int i = 0; i < st->get_child_trees().size(); i++) {
			SyntaxTree* child = &(st->get_child_trees()[i]);
			compile(child, scope_table);
		
		}

		file << "add esp," << scope_table->table.size() * 4 << endl;
		var_counter -= scope_table->table.size();
				
		delete scope_table;
		file << lbl  << ":\n";
		
		within_scope--;
		return "";	
			
	}


	else if(root->getTToken() == "FCALL") {
			
		for(int i = st->get_function_parameters().size()-1; i > -1; i--) {
			string param = compile(&(st->get_function_parameters()[i]), symbol_table);
			file << "push " << param << endl;
		}

		file << "call " << root->getTValue() << endl;
		file << "add esp," << st->get_function_parameters().size() * 4 << endl;
		return root->getTValue();
	
	}


	
	file.close();
	return "";
}
