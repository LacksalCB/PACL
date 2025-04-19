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

ast_t* parser_parse_statements(token_t** token_list, int* token_count);
ast_t** parser_parse(token_t** token_list, int* token_count);

#endif /* PACL_PARSER_H */
