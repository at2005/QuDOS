

#include "compiler.h"


using namespace std;



int main(int argc, char** argv) {

	
	vector<Pair> token_values = execute_lex(argv[1]).getLex().dict_output;
	vector<vector<Pair>> expressions = getEachExpression(token_values);
	
//	execute_lex("btyste.qpp").getLex().printLex();	
	
	unordered_map<string, SyntaxTree*> func_table = {};
	free_regs = {0,0,0,0,0,0};
	file << "section .text:\nglobal main\n";
	
		
	gate_reg = "esi";

	free_regs.esi = 1;
	
	SyntaxTree* main_tree;
	for(int i = 0; i < expressions.size(); i++) {
		SyntaxTree* st = new SyntaxTree(expressions[i]);
		if(st->get_expr_type() == "FUNCTION_DECLARATION") { 
			
			unordered_map<string, int> flocal_tab = {};			
			rtrack(st, flocal_tab);
			fref_table.insert({st->getRoot()->getTValue(), flocal_tab});
	
					
			//for(auto& it : fref_table) cout << it.first << endl;		
				

			std::unordered_map<string,int> table = {};
			symtab* func_symtab = new symtab;
			func_symtab->table = table;
			func_symtab->var_counter = 0;
			func_symtab->parent_table = nullptr;	

			func_table.insert({st->getRoot()->getTValue(), st});
			
			vector<SyntaxTree> func_params = st->get_function_parameters();
			
			

			for(int j = 0; j < func_params.size(); j++) {
				cout << func_params[j].getRoot()->getTValue() << endl;
				func_symtab->table.insert({func_params[j].getRoot()->getTValue(), func_symtab->var_counter});
				func_symtab->var_counter++;
			}


			file << st->getRoot()->getTValue() << ":\n";

			quant_reg = "ebx";			
//			string fr = get_free_reg();
//			quant_reg = fr;
	
			if(st->getRoot()->getTValue() == "main") {
			file << "mov dword [__q__]," << quant_reg << endl;
				file << "mov " << "esi" << ", QGATE\n";
//				gate_reg = "esi";
			}

			for(int i = 0; i < st->get_child_trees().size(); i++) { 
				compile(&(st->get_child_trees()[i]), func_symtab);	
			}

			file << "db 0xC0\n";
			file << "db 0xDE\n\n\n";	
			func_symtab->var_counter = 0;
			free_reg("eax");
		}

		else compile(st, new symtab);
				
	
	}

	data_section += "__q__ dd 0\n";
	file << data_section << endl;
	file << bss_section;
	return 0;



}
