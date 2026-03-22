#ifndef PACL_AST_H
#define PACL_AST_H

#include <stdlib.h>

#define bool int

typedef struct AST_STRUCT{
	// AST Types
	enum {
		AST_ROOT,

		// N-ary compounds
		AST_COMPOUND,

		// N-ary statements
		AST_STATEMENT_ASSIGNMENT,
		AST_STATEMENT_IF,
		AST_STATEMENT_FOR,
		AST_STATEMENT_WHILE,
		AST_STATEMENT_RETURN,

		// Unary expressions
		AST_EXPRESSION_NOT,

		// Binary Expressions
		AST_EXPRESSION_ADD,
		AST_EXPRESSION_SUB,
		AST_EXPRESSION_MUL,
		AST_EXPRESSION_DIV,
		AST_EXPRESSION_AND,
		AST_EXPRESSION_OR,

		// Unary op format
		AST_UN_OP,

		// Binary op format
		AST_BIN_OP,
		AST_VAR,
		AST_NUM
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
ast_t** init_compound();

void print_ast(ast_t* ast);

#endif /* PACL_AST_H */


