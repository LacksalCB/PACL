#include "include/ir_generator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ir_T* init_ir(){
	ir_T* ir = malloc(1*sizeof(struct IR_STRUCT));
	ir->token = malloc(1*sizeof(char));
	ir->size = 0;
	return ir;
}

ir_T* ir_variable(ir_T* ir, ast_T* ast){
	printf("%d\n", ast->var_type);
	switch(ast->var_type){
		case INT:
			printf("INT\n");
			break;
		case STRING:
			printf("STRING\n");
			break;
		default:
			printf("[IR] INVALID TYPE\n"); exit(1);
	}
	return ir;
}

void generate_ir(ir_T* ir, ast_T* ast){
	switch (ast->type){
		case AST_FUNCTION_DEF:
			printf("FUNCTION\n"); break;
		case AST_VARIABLE_DEF:
			printf("VARIABLE\n"); 
			ir_variable(ir, ast);
			break;
		default:
			printf("How, and what the hell\n"); break;
	}
}

