
#include "general/read.h"
//#include "lexer/Lexer.h"
using namespace std;


int main() {
	vector<Pair> token_values = execute_lex("program.qpp").getLex().dict_output;
	for(int i = 0; i < token_values.size(); i++) {
		cout << token_values[i].getToken() << endl;
		cout << token_values[i].getValue() << endl;
	
	}

}
