#ifndef PACL_AST_H
#define PACL_AST_H

#include <stdlib.h>

#define bool int

typedef struct AST_STRUCT{
	// AST Types
	enum{
		// Basic Types
		AST_INT, 			//0
		AST_FLOAT, 			//1
		AST_DOUBLE, 		//2
		AST_CHAR, 			//3 
		AST_STRING, 		//4
		AST_BOOL, 			//5

		// Math Types
		AST_EXPRESSION, 	//6

		// Complex Types
		AST_STRUCT, 		//7
		AST_ENUM, 			//8

		// Function Types
		AST_FUNCTION_DEF, 	//9
				AST_FUNCTION_CALL, 	//10
		AST_ARGUMENT, 		//11
		AST_RETURN, 		//12

		// Variable types
		AST_VARIABLE_DEF, 	//13
		AST_VARIABLE_CALL, 	//14

		// Compound Types
		AST_COMPOUND,		//15
		AST_STATEMENT 		//16
	}type;
	
	//types
	enum{
		INT, 				//0
		FLOAT, 				//1
		DOUBLE, 			//2
		CHAR, 				//3
		STRING, 			//4
		BOOL, 				//5
		VOID 				//6
	}def_type;

	// EXPRESSIONS
	int expression_type;
	char* expression_op;
	struct AST_STRUCT* expression_left;
	struct AST_STRUCT* expression_right;

	// VARIABLE DEFINITION
	char* var_def_type;
	int var_type;
	char* var_def_name;
	struct AST_STRUCT* var_def_value;
	
	// VARIABLE DEFINITION VALUES
	int int_value;
	float float_value;
	double double_value;
	char char_value;
	char* string_value;
	bool bool_value;

	// FUNCTION DEFINITION
	char* fn_def_type;
	int fn_type;
	char* fn_def_name;

	// ARGUMENT DEFINITION
	struct AST_STRUCT** fn_def_args;
	size_t fn_def_args_size;
	char* arg_type;
	char* arg_name;
	struct AST_STRUCT* arg_def_value;

	// RETURN STATEMENTS
	struct AST_STRUCT* return_value;

	// VARIABLE CALL
	char* var_name;
	
	// FUNCTION CALL
	char* fn_call_name;
	char** fn_call_args;
	
	struct AST_STRUCT** compound_value;
	size_t compound_size;

}ast_T;

ast_T* init_ast(int type);

#endif /* PACL_AST_H */
