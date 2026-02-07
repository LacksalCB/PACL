#ifndef PACL_PARSER_H
#define PACL_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT{
	token_t** tokens;
	int current_token_index;
	token_t* current_token;
}parser_t;

parser_t* init_parser(token_t** tokeen_list);

int parser_eat(parser_t* parser);

ast_t* parse_statement(parser_t* parser);
ast_t* parse_expression(parser_t* parser);
ast_t* parse_term(parser_t* parser);
ast_t* parse_factor(parser_t* parser);
char* parse_tok(parser_t* parser);

ast_t* parser_parse(token_t** token_list);

#endif /* PACL_PARSER_H */
