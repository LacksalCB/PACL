#ifndef PACL_AST_H
#define PACL_AST_H

#include <stdlib.h>

#define bool int

typedef struct AST_STRUCT{
	// AST Types
	enum{
		AST_VARIABLE, 		//0
		AST_CONSTANT, 		//1
		AST_OPERATOR, 		//2
		
		AST_COMPOUND,		//15
		AST_STATEMENT 		//16
	}type;
	
	// EXPRESSIONS
	int expression_type;
	char* expression_op;
	struct AST_STRUCT* expression_left;
	struct AST_STRUCT* expression_right;
	
	struct AST_STRUCT** compound_value;
	size_t compound_size;

}ast_t;

ast_t* init_ast(int type);

#endif /* PACL_AST_H */
