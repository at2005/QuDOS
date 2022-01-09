#ifndef COMPILER_H
#define COMPILER_H

#include <stddef.h>
#include <unordered_map>
#include "parser/SyntaxTree.h"
#include <fstream>
#include "general/read.h"
#include "general/BaseConversion.h"
#include "rtrack.h"

#define ADD_X86 "add"
#define SUB_X86 "sub"
#define MUL_X86 "imul"
#define DIV_X86 "div"
#define IDIV_X86 "idiv"

#define JMP_X86 "jmp"
#define JE_X86 "je"
#define JNE_X86 "jne"
#define JG_X86 "jg"
#define JGE_X86 "jge"
#define JL_X86 "jl"
#define JLE_X86 "jle"

#define CALL_X86 "call"
#define RET_X86 "ret"

#define SETE_X86 "sete"
#define SETNE_X86 "setne"
#define SETG_X86 "setg"
#define SETGE_X86 "setge"
#define SETL_X86 "setl"
#define SETLE_X86 "setle"

#define MOV_X86 "mov"
#define CMP_X86 "cmp"


// create global variables
// jmp_flag is set during compilation of test condition
static int jmp_flag = 0;
static int cond_flag = 0;
// label counter
static int counter = 0;
// variable counter
//static int symbol_table->var_counter = 0;
// count number of strings
static int string_counter = 0;

bool is_left = false;

unordered_map<string, unordered_map<string, int>> fref_table = {};

// file descriptor for output
static ofstream file("./out.asm");
// string corresponding to data section of file
string data_section = "section .data:\n";
string bss_section = "section .bss:\n";
string quant_reg = "";
string gate_reg = "";
// structure for symbol table
typedef struct symtab {
	std::unordered_map<string, int> table;
	struct symtab* parent_table;
	int var_counter;

} symtab;


// holds the status of each register
static struct  {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;

} free_regs;


// recursive search the symbol table
int search_symtab(symtab* tab, string var_name) {
	
	if(tab == nullptr) {
		cerr << "VARIABLE " << var_name << " NOT DECLARED OR NOT IN SCOPE!\n";
	       	exit(1);
	}

	if(tab->table.find(var_name) != tab->table.end()) {
		return tab->table.find(var_name)->second;

	}


	return search_symtab(tab->parent_table, var_name);
	



}


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


void mov_x86(string reg0, string reg1) {
	if(reg0 != reg1) file << MOV_X86 << " " << reg0 << "," << reg1 << endl;

}


void cmp_x86(string reg0, string reg1) {
	file << CMP_X86 << " " << reg0 << "," << reg1 << endl;

}


void inc_esp_x86(unsigned int size) {
	if(size != 0)  file << "add esp," << size << endl;

}

void call_x86(string func_name) {
	file << "call " << func_name << endl;

}

void push_x86(string val, string type) {
	file << "push " << type << " " << val << endl;

}


string compile(SyntaxTree* st, symtab* symbol_table ) {
	// get root of AST
	Node* root = st->getRoot();

	if(root->getTValue() != "else" && cond_flag) {
		cout << root->getTValue() << endl;
		cond_flag = 0;
		file << "l" + to_string(counter) << ":\n";
		counter++;
	}

	// if operator
	if(root->getTToken() == "OPERATOR") { 

		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		
		// compile children
		is_left = true;
		string lreg = compile(&left_tree, symbol_table);
//		is_left = true;
		string rreg = compile(&right_tree, symbol_table);

		
		// if the left child is an identifier move it into a register
		if(root->getLeftChild()->getTToken() == "IDENTIFIER" && !isAppendOperator(root->getTValue())) {
			string temp_reg = get_free_reg();
			mov_x86(temp_reg, lreg);
			lreg = temp_reg;

		}

		
		if(root->getTValue() == "%") {
			mov_x86(rreg, "0");
			mov_x86(rreg, lreg);
			file << "and " << rreg << ", 0x1\n";
			//file << "xor " << rreg << ", 0x1\n";
			free_reg(lreg);
			return rreg;
		
		//	return "";
		}		

		// set operation type based on instruction
		string op_type = "";
		if(root->getTValue() == "+" || root->getTValue() == "+=") op_type = ADD_X86;
		else if(root->getTValue() == "-" || root->getTValue() == "-=") op_type = SUB_X86;
		else if (root->getTValue() == "*" || root->getTValue() == "*=") op_type = MUL_X86;
	
		else if(root->getTValue() == "/" || root->getTValue() == "/=") {
			op_type = IDIV_X86;
			int eax_free = free_regs.eax;
			int edx_free = free_regs.edx;
			free_regs.edx = 1;
			free_regs.eax = 1;	
			file << "push edx\n";
			file << "push eax\n";
			// inc var counter since we've pushed two regs to stack
			symbol_table->var_counter += 2;	
			is_left = true;
			string lreg = compile(&left_tree, symbol_table);
			string rreg = compile(&right_tree, symbol_table);
			mov_x86("edx", "0");
			mov_x86("eax", lreg);
			file << op_type << " " << rreg << endl;
			string div_res = get_free_reg();
			mov_x86(div_res, "eax");
			file << "pop eax\n";
			file << "pop edx\n";
			symbol_table->var_counter -= 2;
			free_regs.eax = eax_free;
			free_regs.edx = edx_free;

			if(root->getTValue() == "/=") {
				mov_x86(lreg, div_res);
				free_reg(rreg);
				return lreg;	
			
			}

			free_reg(rreg);
			free_reg(lreg);
			return div_res;
		}

		file << op_type << " " << lreg << "," << rreg << endl;
		free_reg(rreg);
		
		return lreg;
	}


	// case if tree corresponds to a relational operation

	else if(root->getTToken() == "COMPARISON_OPERATOR") {
		SyntaxTree left_tree = SyntaxTree(root->getLeftChild());
		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
	
		is_left = true;
		string lreg = compile(&left_tree, symbol_table);
		string rreg = compile(&right_tree, symbol_table);
		
		// move into register if left operand is an identifier
		if(root->getLeftChild()->getTToken() == "IDENTIFIER") {
			string reg = get_free_reg();
			mov_x86(reg, lreg);
			lreg = reg;
		
		}

		// compare operands
		cmp_x86(lreg, rreg);
		
		// free left register
		if(root->getLeftChild()->getTToken() == "IDENTIFIER") free_reg(rreg);
		
		
		string cmp_type = "";
		
		// set cmp_type to either a set or a jump. Latter is useful
		// for conds/loops and former for using result in another operation
		if(root->getTValue() == ">") {
			if(!jmp_flag) cmp_type = SETG_X86; 
			else cmp_type = JLE_X86;
		}
		
		else if(root->getTValue() == ">=") {
			if(!jmp_flag) cmp_type = SETGE_X86;
		       	else cmp_type = JL_X86;
		}

		else if(root->getTValue() == "<") {
			if(!jmp_flag) cmp_type = SETL_X86;
		       	else cmp_type = JGE_X86;
		}

		else if(root->getTValue() == "<=") {
			if(!jmp_flag) cmp_type = SETLE_X86;
		       	else cmp_type = JG_X86;
		}

		else if(root->getTValue() == "==") {
			if(!jmp_flag) cmp_type = SETE_X86;
		       	else cmp_type = JNE_X86;
		}

		else if(root->getTValue() == "!=") {
		       	if(!jmp_flag) cmp_type = SETNE_X86;
		       	else cmp_type = JE_X86;
		}
		
		if(!jmp_flag) {
			string reg = get_free_reg();
			string byte_reg = get_byte_reg(reg);
			file << "and " << reg << "," << "0x0" << endl;	
			file << cmp_type << " " << byte_reg << endl;
			return reg;	
		}
		

		free_reg(lreg);
		free_reg(rreg);	
		string label = "l" + to_string(counter);
		cout << "label: " << label << endl;	
		counter++;
		file << cmp_type << " " << label << endl;
		return label;			
	
	}	


	else if(root->getTToken() == "NUMBER") {
		
		if(is_left) {
			string val = root->getTValue();
			string freg = get_free_reg();
			mov_x86(freg, val);
			is_left = false;
			return freg;
		}

		return root->getTValue();
	}		

	else if(root->getTToken() == "IDENTIFIER") {
		int pos = search_symtab(symbol_table, root->getTValue());
		string offset =  to_string(4*(symbol_table->var_counter - (pos + 1)));	
		string val = " dword [esp+" + (offset) + "]";
		if(root->is_classical()) {
			string reg = get_free_reg();
			mov_x86(reg, val);
		
			SyntaxTree subs = SyntaxTree(new Node(Pair(root->getPurpose(), "IDENTIFIER")));
			
			file << "add " << reg << "," << compile(&subs, symbol_table) << endl;
			return "[" + reg + "]";

		}

		return val;	
	
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
		symbol_table->table.insert({var_name, symbol_table->var_counter});
		
		if(isNumeric(root->getPurpose())) {
			bss_section += "num resb 256\n";	
			file << "push num\n";
			symbol_table->var_counter++;
			return "num";	
		}

		
		if(root->getLeftChild()->getPurpose() == "float") {
			float num = stof(root->getRightChild()->getTValue());
			uint32_t exp = to_binary((int)num).size() + 126;
			string mts_str = to_binary((int)num) + to_bin_float(num);
			string temp(24-mts_str.size(), '0');
			mts_str += temp;
			mts_str[0] = '0';
			uint32_t mantissa = to_decimal(mts_str);
			uint32_t res = mantissa | (exp << 23) | 0x00000000;
					

			//cout << to_binary((int)num) << " : " << to_bin_float(num) << endl;
			file << "push dword 0b" << to_binary(res) << endl;
			file << "fld dword [esp]" << endl;
			inc_esp_x86(4);	
			return "st0";
		
		}

		SyntaxTree right_tree = SyntaxTree(root->getRightChild());
		string res = compile(&right_tree, symbol_table);
		
		file << "push " << res << endl;
		free_reg(res);
		symbol_table->var_counter++;
		return res;
	
	}


	else if(root->getTValue() == "if") {
		symtab* scope_table = new symtab;
		scope_table->table = {};
		scope_table->parent_table = symbol_table;
		scope_table->var_counter = symbol_table->var_counter;

		jmp_flag = 1;
		SyntaxTree cond_tree = SyntaxTree(root->getLeftChild());
		string lbl = compile(&cond_tree, symbol_table);	
	
		vector<SyntaxTree> child_trees = st->get_child_trees();

		for(int i = 0; i < child_trees.size(); i++) {
			SyntaxTree* child = &(child_trees[i]);
			string stuff = compile(child, scope_table);
			free_reg(stuff);
		
		}

		inc_esp_x86(scope_table->table.size()*4);
		symbol_table->var_counter -= scope_table->table.size();
				
		delete scope_table;
		file << "jmp " << "l" + to_string(counter) << endl;
		file << lbl  << ":\n";
		cond_flag = 1;	
		return "";	
			
	}

	else if(root->getTValue() == "else") {
		cond_flag = 0;
		symtab* scope_table = new symtab;
		scope_table->table = {};
		scope_table->parent_table = symbol_table;
		scope_table->var_counter = symbol_table->var_counter;

		vector<SyntaxTree> child_trees = st->get_child_trees();

		for(int i = 0; i < child_trees.size(); i++) {
			SyntaxTree* child = &(child_trees[i]);
			compile(child, scope_table);
		
		}

		cond_flag = 1;
		delete scope_table;
		return "";
	
	}

	else if(root->getTValue() == "asm") {
		if(root->getTValue() == "asm") {
			file << st->get_function_parameters()[0].getRoot()->getTValue() << endl;
		
		}
		

			
	}

	else if(root->getTValue() == "addr") {
		string param =  st->get_function_parameters()[0].getRoot()->getTValue();
		string reg = get_free_reg();
		int pos = search_symtab(symbol_table, param);
		string offset =  to_string(4*(symbol_table->var_counter - (pos + 1)));	
		mov_x86(reg, "esp");
		file << "add " << reg << "," << offset << endl;	
		//return  "(esp+"+offset+")";
		return reg;

	
	}

	else if(root->getTValue() == "copy") {
		string param1 =  compile(&(st->get_function_parameters()[0]), symbol_table);
		string param2 =  compile(&(st->get_function_parameters()[1]), symbol_table);
		string reg = get_free_reg();
		mov_x86(reg, param2);
		mov_x86(param1, reg);
		free_reg(param1);
		free_reg(param2);
		free_reg(reg);
		return "";


	}

	else if(root->getTToken() == "FCALL" && !isAssembly(root->getTValue())) {
		vector<SyntaxTree> func_params = st->get_function_parameters();	
		int vc_copy = symbol_table->var_counter;
//		file << "push edi\npush esi\npush edx\npush ecx\npush ebx\n";
		file << "push edi\npush esi\npush edx\npush ecx\n";
	//	symbol_table->var_counter += 5;
		symbol_table->var_counter += 4;
		for(int i = func_params.size()-1; i > -1; i--) {
			string param = compile(&(func_params[i]), symbol_table);
			symbol_table->var_counter++;
			file << "push " << param << endl;
			free_reg(param);
		}

		symbol_table->var_counter = vc_copy;
		cout << func_params.size() << " : " << root->getTValue() << endl;
		file << "call " << root->getTValue() << endl;
		inc_esp_x86(func_params.size() * 4);
	//	file << "pop ebx\npop ecx\npop edx\npop esi\npop edi\n";
		file << "pop ecx\npop edx\npop esi\npop edi\n";
		return "eax";
	
	}

	else if(isAssembly(root->getTValue())) {
		string opcode = "";
		if(root->getTValue() == "H") opcode = "0x0";
		else if(root->getTValue() == "X") opcode = "0x1";
		else if(root->getTValue() == "Y") opcode = "0x2";
		else if(root->getTValue() == "Z") opcode = "0x3";
		else if(root->getTValue() == "ID") opcode = "0x4";
		else if(root->getTValue() == "CX") opcode = "0x5";
		else if(root->getTValue() == "RX") opcode = "0x6";
		else if(root->getTValue() == "MEASURE") opcode = "0xF";
		vector<SyntaxTree> func_params = st->get_function_parameters();
		string param = compile(&(func_params[0]), symbol_table);
		string opt = "0";
		if(func_params.size() == 2) opt = compile(&(func_params[1]), symbol_table);
		
		//file << "push ebx\npush ecx\npush edx\npush esi\npush edi\n";	
		//file << "push " << quant_reg << endl;
		file << "push " << opt << endl;
		file << "push " << param << endl; 
		file << "push " << opcode << endl;
		file << "call " << gate_reg << endl;
		free_reg(param);
		free_reg(opt);
		inc_esp_x86(12);
		//file << "pop edi\npop esi\npop edx\npop ecx\npop ebx\n";	

		
	
	}

	else if(root->getTToken() == "KEYWORD") {
		if(root->getTValue() == "qrun") file << "mov byte [ebx], 0xD\npushad\npush dword [__q__]\ncall qrun\nadd esp, 4\npopad\n";
		else if (root->getTValue() == "link") {
			string func_name = st->get_function_parameters()[0].getRoot()->getTValue();
			file << "[extern " << func_name << "]\n";

		}

		else if(root->getTValue() == "nloc") {
			string func_name = st->get_function_parameters()[0].getRoot()->getTValue();
			
			data_section += "msg_" + func_name + " db " + "\"" + func_name + "\",0\n";
			string temp = "msg_" + func_name;
			
			file << "pushad\npush " << temp << endl << "push " << func_name << endl << "call sendq\nadd esp,8\npopad\n";
			
			for(auto& i : fref_table[func_name]) {
				//cout << i.first << endl;
				file << "pushad\npush " << "msg_" + i.first << endl << "push " << i.first << endl << "call sendq\nadd esp,8\npopad\n";
				data_section += "msg_" + i.first + " db " + "\"" + i.first + "\",0\n";
			}

			mov_x86("[ebx]", "byte 0xA");
			file << "inc ebx\n";	
			push_x86(temp, "dword");
			push_x86("ebx", "dword");
			call_x86("strcpy");
			mov_x86("ebx", "eax");
			inc_esp_x86(8);



		}

		else if(root->getTValue() == "async") {	
			string func_name = st->get_function_parameters()[0].getRoot()->getTValue();
			file << "pushad\npush " << func_name << endl << "call asyncq\nadd esp,4\npopad\n";
			

		}

		else if(root->getTValue() == "return") {
			if(st->get_function_parameters().size() != 0) {
				SyntaxTree param = st->get_function_parameters()[0];
				string obj_to_ret = compile(&(param), symbol_table);
				mov_x86("eax", obj_to_ret);

			}
			
			file << "l" + to_string(counter++) << ":\n";
			inc_esp_x86(symbol_table->var_counter*4);
				
			file << "ret\n";

		}
	
	
	}



	else if(root->getTValue() == "for") {
		
		symtab* loop_scope = new symtab;
		loop_scope->table = {};
		loop_scope->parent_table = symbol_table;	
		loop_scope->var_counter = symbol_table->var_counter;
		vector<SyntaxTree> func_params = st->get_function_parameters();
		compile(&(func_params[0]), loop_scope);
		string jmp_label =  "l" + to_string(counter);
		file << jmp_label << ":\n";
	       	counter++;
		
		jmp_flag = 1;
		string break_label = compile(&(func_params[1]), loop_scope);
		
		vector<SyntaxTree> child_trees = st->get_child_trees();
		
		for(int i = 0; i < child_trees.size(); i++) {
			compile(&(child_trees[i]),loop_scope);
		
		}

		compile(&(func_params[2]), loop_scope);
			
		inc_esp_x86((loop_scope->table.size()-1) * 4);
		file << "jmp " << jmp_label << endl;
			
		file << break_label << ":\n";	
		inc_esp_x86(4);
		delete loop_scope;
		return break_label;		
	
	}


	else if(root->getTValue() == "while") {
		
		symtab* loop_scope = new symtab;
		loop_scope->parent_table = symbol_table;
		loop_scope->table = {};
		loop_scope->var_counter = symbol_table->var_counter;
		vector<SyntaxTree> func_params = st->get_function_parameters();
		jmp_flag = 1;
		string jmp_label = "l" + to_string(counter);
		counter++;
	       	file << jmp_label << ":" << endl;	
		SyntaxTree cond_tree = SyntaxTree(root->getLeftChild());
		string break_label = compile(&cond_tree, symbol_table);
		vector<SyntaxTree> child_trees = st->get_child_trees();

		for(int i = 0; i < child_trees.size(); i++) {
			compile(&(child_trees[i]),loop_scope);
		
		}
		
		file << "jmp " << jmp_label << endl;
	
		file << break_label << ":\n";
		
		delete loop_scope;
		return break_label;

	
	
	}
	
	return "";
}


#endif
