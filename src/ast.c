#include "../include/ast.h"

#include <stdio.h>

ast_t* init_child(int type){
	ast_t* ast = malloc(1*sizeof(struct AST_STRUCT));
	ast->type = type;
	ast->value = NULL;

	ast->L = NULL;
	ast->R = NULL;

	ast->children = NULL;
	printf("%d\n",ast->type);

	return ast;
}

ast_t** init_compound(int size){
	ast_t** ast = malloc((size+1)*sizeof(struct AST_STRUCT*));
	ast[size] = NULL;

	return ast;
}
