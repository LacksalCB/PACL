#ifndef PACL_AST_H
#define PACL_AST_H

#include <stdlib.h>

#define bool int

typedef struct AST_STRUCT{
	// AST Types
	enum {
		AST_STATEMENT,

		AST_EXPRESSION,
		AST_TERM,
		AST_FACTOR,
		AST_ID,	
	
		// STRUCTURAL 			
		AST_COMPOUND 			
	}type;

	struct AST_STRUCT* statement;
	struct AST_STRUCT* expression;
	struct AST_STRUCT* term;
	struct AST_STRUCT* factor;
	char* op;
	char* id;
	char* num;

	struct AST_STRUCT** compound_value;
	size_t compound_size;

}ast_t;

ast_t* init_ast(int type);

void print_ast(ast_t* ast);

#endif /* PACL_AST_H */
