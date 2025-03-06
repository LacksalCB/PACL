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

