#include "../include/compiler.h"

#include <stdio.h>

char* buff;
token_t** token_list;
int token_count = 0;
ast_t* ast;

void dealloc() {
	free(buff);

	for (int i = 1; i < token_count; i++) {
		free(token_list[i-1]->value);
		free(token_list[i-1]);
	}
	free(token_list[token_count]);
	
	free(token_list);

	for (int i = 0; i < 1; i++) {
		//free(ast[i]);
	}
	free(ast->statement->expression->term->factor->id);
}

int main(int argc, char** argv){
	for (int i = 0; i < argc; i += 1) {
		// Do stuff for multiple args
	}

	buff = read_file(argv[1]);
	token_list = lexer_tokenize(buff, &token_count);
	ast = parser_parse(token_list);
	
	dealloc();
	return 0;
}
