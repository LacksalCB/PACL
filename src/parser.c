#include "../include/parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

parser_t* init_parser(lexer_t* lexer){
	parser_t* parser = malloc(1*sizeof(struct PARSER_STRUCT));
	parser->lexer = lexer;	
	parser->current_token = lexer_advance(parser->lexer);
	return parser;
}

void parser_eat(parser_t* parser, int type){
	if((int)parser->current_token->type == type){
		parser->current_token = lexer_advance(parser->lexer);
	}else{
		printf("[PARSER] Error unexpected token \"%s\" with type: %d\n[PARSER] Expected type: %d\n", parser->current_token->value, type, parser->current_token->type);
		exit(1);
	}
}

ast_t* parser_parse_statement(token_t** token_list, int* token_count) {
	
	ast_t* ast = malloc(1 * sizeof(struct AST_STRUCT));	
	return ast;
}

ast_t** parser_parse(token_t** token_list, int* token_count) {
	for (int i = 0; i < *token_count; i++) {
		printf("%s, %d\n", token_list[i]->value, token_list[i]->type);
	}

	ast_t** ast = malloc(1 * sizeof(struct AST_STRUCT*));

	return ast;
}

