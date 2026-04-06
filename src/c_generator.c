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

// Thank you chatgpt for this print function
void write_from_ast(ast_t* ast, char** c_file, size_t* c_len) {
    if (!ast) return;

    switch(ast->type) {
        case AST_VAR:
           	
            return;
        case AST_NUM:
            printf("AST_NUM (Value = '%s')\n", ast->value);
            return;
        case AST_COMPOUND:
            puts("COMPOUND ->");
            for (int i = 0; ast->children && ast->children[i]; i++) {
                write_from_ast(ast->children[i], c_file, c_len);
            }
            return;
        default:
            // For operator nodes, use value string if present
            printf("%s ->\n", ast->value ? ast->value : "UNKNOWN");
            break;
    }

    // Recurse on L and R if they exist
    if (ast->L) write_from_ast(ast->L, c_file, c_len);
    if (ast->R) write_from_ast(ast->R, c_file, c_len);
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
