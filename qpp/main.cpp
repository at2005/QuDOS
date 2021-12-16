

#include "compiler.h"


using namespace std;



int main() {

	
	vector<Pair> token_values = execute_lex("program.qpp").getLex().dict_output;
	vector<vector<Pair>> expressions = getEachExpression(token_values);
	
//	execute_lex("program.qpp").getLex().printLex();	
	
	free_regs = {0,0,0,0,0,0};
	file << "section .text:\nglobal main\n";
	
	std::unordered_map<string,int> mtable = {};
	symtab* main_table = new symtab;
	main_table->table = mtable;
	
	main_table->parent_table = nullptr;	
	
	
	unordered_map<string, SyntaxTree*> func_table = {};

		
gate_reg = "esi";

	SyntaxTree* main_tree;
	for(int i = 0; i < expressions.size(); i++) {
		SyntaxTree* st = new SyntaxTree(expressions[i]);
		if(st->get_expr_type() == "FUNCTION_DECLARATION") { 
			
			func_table.insert({st->getRoot()->getTValue(), st});

			file << st->getRoot()->getTValue() << ":\n";
			
			if(st->getRoot()->getTValue() == "main") {
				string fr = get_free_reg();
				quant_reg = fr;
				file << "call quant\nmov " << fr << ",eax\nmov dword [__q__], eax\n";
//				file << "mov " << "esi" << ", QGATE\n";
//				gate_reg = "esi";
			}

			for(int i = 0; i < st->get_child_trees().size(); i++) { 
				compile(&(st->get_child_trees()[i]), main_table);	
			}

			file << "db 0xC0\n";
			file << "db 0xDE\n";	
			var_counter = 0;
			free_reg("eax");
		}

		else compile(st, main_table);
				
	
	}

	data_section += "__q__ dd 0\n";
	file << data_section << endl;
	file << bss_section;
	return 0;



}
