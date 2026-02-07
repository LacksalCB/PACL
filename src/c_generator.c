#include "../include/c_generator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/IO.h"

#define FIRST_CHAR 33

/*
void prepend_includes(char* out) {
	

}
*/

void write_from_ast(const ast_t* ast, char** c_file, size_t* c_len) {
	size_t cap = 128;
	size_t len = 0;
	char* out = malloc(cap);

	int curr_type = ast->type;
	switch(curr_type) {
		case AST_COMPOUND:
			print_ast(ast->statement);
			break;	
		case AST_STATEMENT:
			print_ast(ast->expression);
			break;
		case AST_EXPRESSION:
			print_ast(ast->term);
			break;
		case AST_TERM:
			print_ast(ast->factor);
			break;
		case AST_FACTOR:
 			int needed = snprintf(NULL, 0, "int %s%s%s", ast->id, ast->op, ast->num);
			if ((size_t) needed + 1 > cap) {
				cap = needed + 1;
				out = realloc(out, cap);
			}	
		
			snprintf(out, cap, "int %s%s%s", ast->id, ast->op, ast->num);
			len = needed;
			break;
	};

	char* rest = strdup(*c_file + FIRST_CHAR);	
	size_t rest_len = strlen(rest);
	
	*c_file = realloc(*c_file, FIRST_CHAR + len + rest_len + 1);
	
	memcpy(*c_file + FIRST_CHAR, out, len);
	strcpy(*c_file + FIRST_CHAR + len, rest);

	free(rest);
	free(out);
}

#define MAIN_SIZE 50 
// Format and make a basic C main function
char* append_c_main() {
	return "int main(int argc, char** argv) {\n\n  return 0;\n}\n";
}

char* generate_c_ir(const ast_t* ast){
	char* c_file = strdup(append_c_main());
	size_t c_len = strlen(c_file);

	write_from_ast(ast, &c_file, &c_len);
	
	return c_file;
}

