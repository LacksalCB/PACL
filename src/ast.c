#include "../include/ast.h"

#include <stdio.h>

ast_t* init_child(int type){
	ast_t* ast = malloc(1*sizeof(struct AST_STRUCT));
	ast->type = type;
	printf("%d\n",ast->type);

	return ast;
}

ast_t** init_compound(){
	ast_t** ast = malloc(1*sizeof(struct AST_STRUCT*));

	return ast;
}
