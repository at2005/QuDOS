
#include "general/read.h"
//#include "lexer/Lexer.h"
#include "parser/SyntaxTree.h"


using namespace std;


int main() {
	vector<Pair> token_values = execute_lex("program.qpp").getLex().dict_output;
	vector<vector<Pair>> expressions = getEachExpression(token_values);
	
	
	SyntaxTree* main_tree;
	for(int i = 0; i < expressions.size(); i++) {
		SyntaxTree* st = new SyntaxTree(expressions[i]);
		if(st->getRoot()->getTValue() == "main") {
			//*main_tree = *st;
			main_tree = st;
				
		}
	
	}

	Node* root = main_tree->getRoot();
	
	
	
	

	return 0;



}
