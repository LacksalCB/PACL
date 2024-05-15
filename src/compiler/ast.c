#include "include/ast.h"

#define true  0
#define false 1

ast_T* init_ast(int type){
	ast_T* ast = malloc(1*sizeof(struct AST_STRUCT));
	ast->type = type;

	ast->expression_type = 0;
	ast->expression_op = (void*)0;
	ast->expression_left = (void*)0;
	ast->expression_right = (void*)0;

	ast->var_def_type = (void*)0;
	ast->var_type = 0;
	ast->var_def_name = (void*)0;
	ast->var_def_value = (void*)0;

	ast->int_value = 0;
	ast->float_value = 0.0;
	ast->double_value = 0.0;
	ast->char_value = '\0';
	ast->string_value = (void*)0;
	ast->bool_value = true;

	ast->fn_def_type = (void*)0;
	ast->fn_type = 0;
	ast->fn_def_name = (void*)0;

	ast->fn_def_args = (void*)0;
	ast->fn_def_args_size = 0;
	ast->arg_type = (void*)0;
	ast->arg_name = (void*)0;
	ast->arg_def_value = (void*)0;

	ast->var_name = (void*)0;

	ast->fn_call_name = (void*)0;
	ast->fn_call_args = (void*)0;

	ast->return_value = (void*)0;

	ast->compound_value = (void*)0;
	ast->compound_size = 0;
}
