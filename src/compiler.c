#include "../include/compiler.h"

#include <stdio.h>

char* file;
token_t** token_list;

void dealloc() {
	free(file);
	free(token_list);
}

int main(int argc, char** argv){
	for (int i = 0; i < argc; i += 1) {
		// Do stuff for multiple args
	}

	file = read_file(argv[1]);	
	token_list = tokenize(file);
	//ast_t* root_node = parser_parse_statements(parser);

	dealloc();
	return 0;
}
