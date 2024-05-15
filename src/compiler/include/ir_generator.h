#ifndef PACL_IR_GENERATOR_H
#define PACL_IR_GENERATOR_H

#include "ast.h"

typedef struct IR_STRUCT{
	char* token;
	size_t size;
}ir_T;

ir_T* init_ir();
ir_T* ir_variable(ir_T* ir, ast_T* ast);
void generate_ir(ir_T* ir, ast_T* ast);

#endif /* PACL_IR_GENERATOR_H */
