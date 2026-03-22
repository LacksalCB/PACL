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
	size_t len = 0;
	char* out = malloc(1);
	unsigned int curr_type = ast->type;

	switch(curr_type) {
		case AST_ROOT:
			write_from_ast(ast->children[0], c_file, c_len);
			break;	
		case AST_STATEMENT_ASSIGNMENT:
			int needed = snprintf(NULL, 0, "int %s = %s;", ast->L->value, ast->L->value)+1; 
			out = realloc(out, needed);

			len = needed;
			snprintf(out, len, "int %s = %s;", ast->L->value, ast->R->value);
			out[len-1] = 0;
			break;
		case AST_EXPRESSION_ADD:
			break;
	};

	char* rest = strdup(*c_file + FIRST_CHAR);	
	size_t rest_len = strlen(rest);

	*c_file = realloc(*c_file, FIRST_CHAR + len + rest_len + 1);
	
	memcpy(*c_file + FIRST_CHAR+1, out, len);
	strcpy(*c_file + FIRST_CHAR + len, rest);

	free(rest);
	free(out);

}

#define MAIN_SIZE 50 
// Format and make a basic C main function
char* append_c_main() {
	return "int main(int argc, char** argv) {\n\nreturn 0;\n}\n";
}

char* generate_c_ir(ast_t* ast){
	puts("");
	puts("C CODE:");
	char* c_file = strdup(append_c_main());
	size_t c_len = strlen(c_file);

	write_from_ast(ast, &c_file, &c_len);
	puts(c_file);
	
	return c_file;
}

