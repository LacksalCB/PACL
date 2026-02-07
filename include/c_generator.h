#ifndef PACL_C_IR_GENERATOR_H
#define PACL_C_IR_GENERATOR_H

#include "ast.h"

typedef struct C_IR_STRUCT{
	char* token;
	size_t size;
}c_ir_t;

char* generate_c_ir(const ast_t* ast);

#endif /* PACL_C_IR_GENERATOR_H */
