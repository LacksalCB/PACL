#include "include/parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "include/ir_generator.h"

parser_T* init_parser(lexer_T* lexer){
	parser_T* parser = malloc(1*sizeof(struct PARSER_STRUCT));
	parser->lexer = lexer;	
	parser->current_token = lexer_advance(parser->lexer);
	return parser;
}

void parser_eat(parser_T* parser, int type){
	if(parser->current_token->type == type){
		parser->current_token = lexer_advance(parser->lexer);
	}else{
		printf("[PARSER] Error unexpected token \"%s\" with type: %d\n[PARSER] Expected type: %d\n", parser->current_token->value, type, parser->current_token->type);
		exit(1);
	}
}

ast_T* parser_parse_statement(parser_T* parser){
	ast_T* statement = init_ast(AST_STATEMENT);
	if(parser->current_token->type == TOKEN_ID){
		statement = parser_parse_id(parser);
	}else{
		printf("Unexpected token \"%s\", with type: %d\n", parser->current_token->value, parser->current_token->type);
		exit(1);
	}
	return statement;
}

ast_T* parser_parse_statements(parser_T* parser){
	ast_T* compound = init_ast(AST_COMPOUND);
	ir_T* ir = init_ir();

	compound->compound_value = malloc(1*sizeof(struct AST_STRUCT));
	
	ast_T* ast_statement = parser_parse_statement(parser);
	compound->compound_value[0] = ast_statement;
	generate_ir(ir, ast_statement);  // CALL IR GENERATOR ON TREE

	while(parser->current_token->type == TOKEN_SEMICOLON || parser->current_token->type == TOKEN_RBRACE){
		if (parser->current_token->type == TOKEN_SEMICOLON){
			parser_eat(parser, TOKEN_SEMICOLON);
		}else if(parser->current_token->type == TOKEN_RBRACE){
			parser_eat(parser, TOKEN_RBRACE);
		}

		ast_statement = parser_parse_statement(parser);
		generate_ir(ir, ast_statement);

		compound->compound_size++;
		compound->compound_value = realloc(
			compound->compound_value, compound->compound_size + sizeof(struct AST_STRUCT)
		);
		compound->compound_value[compound->compound_size] = ast_statement;
	}
	return compound;
}

ast_T* parser_parse_id(parser_T* parser){
	ast_T* id = init_ast(AST_IDENTIFIER);
	if(strcmp(parser->current_token->value, "var") == 0){
		parser_eat(parser, TOKEN_ID);
		id = parser_parse_var_def(parser);
	}else if(strcmp(parser->current_token->value, "fn") == 0){
		parser_eat(parser, TOKEN_ID);
		id = parser_parse_fn_def(parser);
	}else{
		parser_parse_expression(parser);
	}
	return id;
}

ast_T* parser_parse_var_def(parser_T* parser){
	ast_T* var_def = init_ast(AST_VARIABLE_DEF);

	parser_eat(parser, TOKEN_COLON);

	var_def->var_def_type = parser_parse_type(parser, var_def)->current_token->value;
	parser_eat(parser, TOKEN_ID);
	var_def->var_def_name = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);

	if(parser->current_token->type == TOKEN_EQ){
		parser_eat(parser, TOKEN_EQ);
		var_def->var_def_value = parser_parse_expression(parser);	
	}

	return var_def;
}

ast_T* parser_parse_var_call(parser_T* parser){

}

ast_T* parser_parse_args(parser_T* parser){
	ast_T* arg = init_ast(AST_ARGUMENT);
	arg->arg_type = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);
	arg->arg_name = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);
	return arg;
}

ast_T* parser_parse_return(parser_T* parser){
	parser_eat(parser, TOKEN_ID);
	ast_T* ast_return = init_ast(AST_RETURN);

	if(parser->current_token->type != TOKEN_SEMICOLON){
		ast_return->return_value = parser_parse_expression(parser);
	}
	parser_eat(parser, TOKEN_SEMICOLON);
	return ast_return;
}

ast_T* parser_parse_fn_def(parser_T* parser){
	ast_T* fn_def = init_ast(AST_FUNCTION_DEF);

	if(parser->current_token->type == TOKEN_COLON){
		parser_eat(parser, TOKEN_COLON);
	}

	fn_def->fn_def_type = parser_parse_type(parser, fn_def)->current_token->value;
	parser_eat(parser, TOKEN_ID);
	fn_def->fn_def_name = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);

	parser_eat(parser, TOKEN_LPAREN);

	fn_def->fn_def_args_size = 0;

	if(parser->current_token->type == TOKEN_RPAREN){
		parser_eat(parser, TOKEN_RPAREN);
		return fn_def;
	}else if(parser->current_token->type == TOKEN_ID){
		while(parser->current_token->type != TOKEN_RPAREN){
			ast_T* fn_def_args = parser_parse_args(parser);

			fn_def->fn_def_args = realloc(
				fn_def->fn_def_args, fn_def->fn_def_args_size + sizeof(struct AST_STRUCT)
			);
			fn_def->fn_def_args[fn_def->fn_def_args_size] = fn_def_args;
			if(parser->current_token->type == TOKEN_COMMA){
				fn_def->fn_def_args_size++;
				parser_eat(parser, TOKEN_COMMA);
			}
		}
		parser_eat(parser, TOKEN_RPAREN);
	}

	if(parser->current_token->type == TOKEN_LBRACE){
		parser_eat(parser, TOKEN_LBRACE);
		parser_parse_return(parser);
	}
	return fn_def;
}

parser_T* parser_parse_type(parser_T* parser, ast_T* ast){
	if(strcmp(parser->current_token->value, "int") == 0){
		ast->var_type = INT;
		return parser;
	}else if(strcmp(parser->current_token->value, "float") == 0){
		ast->var_type = FLOAT;
		return parser;
	}else if(strcmp(parser->current_token->value, "double") == 0){
		ast->var_type = DOUBLE;
		return parser;
	}else if(strcmp(parser->current_token->value, "char") == 0){
		ast->var_type = CHAR;
		return parser;
	}else if(strcmp(parser->current_token->value, "string") == 0){
		ast->var_type = STRING;
		return parser;
	}else if(strcmp(parser->current_token->value, "bool") == 0){
		ast->var_type = BOOL;
		return parser;
	}else if(strcmp(parser->current_token->value, "void") == 0){
		ast->var_type = VOID;
		return parser;	
	}else{
		printf("[PARSER]: ERROR Invalid Type %s\n", parser->current_token->value);
	}
}

int is_num(parser_T* parser){
	for(int i = 0; parser->current_token->value[i] != '\0'; i++){
		if(isdigit(parser->current_token->value[i]) || parser->current_token->value[i] == '.'){
			return 0;
		}
	}
	return 1;
}

int is_al(parser_T* parser){
	for(int i = 0; i < strlen(parser->current_token->value); i++){
		if(isalpha(parser->current_token->value[i])){
			return 0;
		}
	}
	return 1;
}

ast_T* parser_parse_term(parser_T* parser){
	ast_T* ast_term;

	if(is_num(parser) == 0){
		if(strchr(parser->current_token->value, '.') != NULL){
			ast_term = init_ast(AST_FLOAT);
			ast_term->float_value = atoi(parser->current_token->value); 
		}
		ast_term = init_ast(AST_INT);
		ast_term->int_value = atoi(parser->current_token->value);
	}else if(is_al(parser) == 0){
		ast_term = init_ast(AST_STRING);
		ast_term->string_value = malloc(1*sizeof(char));
		ast_term->string_value = realloc(
			ast_term->string_value, strlen(ast_term->string_value)+strlen(parser->current_token->value)+1
		);
		strcpy(ast_term->string_value, parser->current_token->value);
	}
	return ast_term;
}

ast_T* parser_parse_expression(parser_T* parser){
	ast_T* operation = init_ast(AST_EXPRESSION);
	operation->expression_left = parser_parse_term(parser);

	parser_eat(parser, TOKEN_ID);
	
	switch (parser->current_token->type){
		case TOKEN_PLUS: parser_eat(parser, TOKEN_PLUS); break;
		case TOKEN_MINUS: parser_eat(parser, TOKEN_MINUS); break;
		case TOKEN_ASTERISK: parser_eat(parser, TOKEN_ASTERISK); break;
		case TOKEN_SLASH: parser_eat(parser, TOKEN_SLASH); break;
		case TOKEN_MOD: parser_eat(parser, TOKEN_MOD); break;
		case TOKEN_SEMICOLON: return operation;
		default:
			printf("[PARSER] Invalid math operator: %s\n", parser->current_token->value); exit(1);
	}

	operation->expression_op = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);
	operation->expression_right = parser_parse_term(parser);
	return operation;
}
