
#include "parser/SyntaxTree.h"


void rtrack(SyntaxTree* func, unordered_map<string, int>& local_tab) {
	
	if(func->getRoot()->getTToken() == "FCALL") {
		local_tab.insert({func->getRoot()->getTValue(), 1});
		return;

	}

	vector<SyntaxTree> children = func->get_child_trees();
	
	for(int i = 0; i < children.size(); i++) {
		rtrack(&(children[i]), local_tab);
	
	}




	return;
}
