#include "../include/compiler.h"

#include <stdio.h>

char* buff;
token_t** token_list;
int token_count = 0;
ast_t** ast;

void dealloc() {
	free(buff);

	for (int i = 0; i < token_count; i++) {
		free(token_list[i]->value);
		free(token_list[i]);
	}
	
	free(token_list);
	free(ast);
}

int main(int argc, char** argv){
	for (int i = 0; i < argc; i += 1) {
		// Do stuff for multiple args
	}

	buff = read_file(argv[1]);
	token_list = lexer_tokenize(buff, &token_count);
	ast = parser_parse(token_list, &token_count);
	
	dealloc();
	return 0;
}
