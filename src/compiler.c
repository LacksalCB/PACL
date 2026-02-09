#include "../include/compiler.h"

#include <stdio.h>
#include <string.h>

char* buff;
token_t** token_list;
int token_count = 0;
ast_t* ast;
char* out_buff;

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
	free(ast->statement->expression->term->factor->op);
	free(ast->statement->expression->term->factor->num);
	
	free(out_buff);
}

// Hardcoded output files for convenience
void c_compile(char* filename) {
	const char* c_out = "c_out/";
	const char* out = "out/";

	size_t dir_len = strcspn(filename, "/") + 1;
	filename += dir_len;
	size_t len = strlen(filename) - 5;
	filename[len] = 0;
	
	char* c_file = malloc(len + 3 + strlen(c_out));	
	char* exec = malloc(len + 1 + strlen(out));
	
	snprintf(c_file, len + 3 + strlen(c_out), "%s%s.c", c_out, filename);
	snprintf(exec, len + 1 + strlen(out), "%s%s", out, filename);

	char* cmd = malloc(128);
	snprintf(cmd, 128, "/bin/gcc %s -o %s", c_file, exec);

	system(cmd);
}

int main(int argc, char** argv){
	for (int i = 0; i < argc; i += 1) {
		// Do stuff for multiple args
	}

	char* file = argv[1];
	buff = read_file(file);
	token_list = lexer_tokenize(buff, &token_count);
	ast = parser_parse(token_list);
	out_buff = generate_c_ir(ast);
	write_file("c_out/1_test.c", out_buff);
	c_compile(file);

	dealloc();
	return 0;
}
