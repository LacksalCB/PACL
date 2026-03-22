#ifndef PACL_AST_H
#define PACL_AST_H

#include <stdlib.h>

#define bool int

typedef struct AST_STRUCT{
	// AST Types
	enum {
		// N-ary compounds
		AST_COMPOUND, 					// 0

		// N-ary statements
		AST_STATEMENT_ASSIGNMENT, 		// 1
		AST_STATEMENT_IF, 				// 2
		AST_STATEMENT_FOR, 				// 3
		AST_STATEMENT_WHILE, 			// 4
		AST_STATEMENT_RETURN, 			// 5

		// Unary expressions
		AST_EXPRESSION_NOT, 			// 6

		// Binary Expressions
		AST_EXPRESSION_ADD, 			// 7
		AST_EXPRESSION_SUB, 			// 8
		AST_EXPRESSION_MUL, 			// 9
		AST_EXPRESSION_DIV, 			// 10
		AST_EXPRESSION_MOD, 			// 11
		AST_EXPRESSION_AND, 			// 12
		AST_EXPRESSION_OR, 				// 13

		// Unary op format
		AST_UN_OP, 						// 14

		// Binary op format
		AST_BIN_OP, 					// 15
		AST_VAR, 						// 16
		AST_NUM 						// 17
	}type;
	struct AST_STRUCT* root;

	struct AST_STRUCT** children;
	size_t children_size;

	struct AST_STRUCT* child;	

	struct AST_STRUCT* L;
	struct AST_STRUCT* R;

	char* value;
}ast_t;

ast_t* init_child(int type);
ast_t** init_compound(int size);

void print_ast(ast_t* ast, int depth, const char* side);

#endif /* PACL_AST_H */


