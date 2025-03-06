#ifndef PACL_IR_GENERATOR_H
#define PACL_IR_GENERATOR_H

#include "ast.h"

typedef struct IR_STRUCT{
	char* token;
	size_t size;
}ir_t;

ir_t* init_ir();
ir_t* ir_variable(ir_t* ir, ast_t* ast);
void generate_ir(ir_t* ir, ast_t* ast);

#endif /* PACL_IR_GENERATOR_H */
