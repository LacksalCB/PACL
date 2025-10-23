#include "../include/ast.h"

ast_t* init_ast(int type){
	ast_t* ast = malloc(1*sizeof(struct AST_STRUCT));
	ast->type = type;

	return ast;
}

