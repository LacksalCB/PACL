#ifndef PACL_PARSER_H
#define PACL_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT{
	lexer_t* lexer;
	token_t* current_token;
}parser_t;

parser_t* init_parser(lexer_t* lexer);

void parser_eat(parser_t* parser, int type);

#endif /* PACL_PARSER_H */
