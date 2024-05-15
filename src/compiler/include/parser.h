#ifndef PACL_PARSER_H
#define PACL_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT{
	lexer_T* lexer;
	token_T* current_token;
}parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_eat(parser_T* parser, int type);

ast_T* parser_parse_statement(parser_T* parser);
ast_T* parser_parse_statements(parser_T* parser);

ast_T* parser_parse_id(parser_T* parser);
ast_T* parser_parse_var_def(parser_T* parser);
ast_T* parser_parse_args(parser_T* parser);
ast_T* parser_parse_return(parser_T* parser);
ast_T* parser_parse_fn_def(parser_T* parser);
parser_T* parser_parse_type(parser_T* parser, ast_T* ast);
int is_num(parser_T* parser);
ast_T* parser_parse_term(parser_T* parser);
ast_T* parser_parse_expression(parser_T* parse);

#endif /* PACL_PARSER_H */
