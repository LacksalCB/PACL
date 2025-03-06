#include "../include/ast.h"

#define true  0
#define false 1

ast_t* init_ast(int type){
	ast_t* ast = malloc(1*sizeof(struct AST_STRUCT));
	ast->type = type;

	ast->expression_type = 0;
	ast->expression_op = (void*)0;
	ast->expression_left = (void*)0;
	ast->expression_right = (void*)0;	

	ast->compound_value = (void*)0;
	ast->compound_size = 0;
	return ast;
}
