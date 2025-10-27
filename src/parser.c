#include "../include/parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

parser_t* init_parser(token_t** token_list){
	parser_t* parser = malloc(1*sizeof(struct PARSER_STRUCT));
	parser->tokens = token_list;
	parser->current_token_index = 0;
	parser->current_token = token_list[parser->current_token_index];
	return parser;
}

int parser_eat(parser_t* parser) {
	parser->current_token_index += 1;
	parser->current_token = parser->tokens[parser->current_token_index];
	puts(parser->current_token->value);
	return 0;
}

token_t* parser_peak(parser_t* parser, int peak_dist) {
	return parser->tokens[parser->current_token_index+peak_dist];
}

ast_t* parse_statement(parser_t* parser) {
	ast_t* ast = init_ast(AST_STATEMENT);

	token_t* L = parser->current_token;

	parser_eat(parser);
	token_t* OP = parser->current_token;
	parser_eat(parser);
	token_t* R = parser->current_token;
	

	if (parser->current_token->type != TOKEN_ID) {
		// Error, malformed Expression (leading op)
		puts("ERROR: INVALID EXPRESSION");
		exit(1);
	}

	ast->expression = parse_expression(parser);		

	return ast;
}

ast_t* parse_expression(parser_t* parser) {
	ast_t* ast = init_ast(AST_EXPRESSION);

	if (parser_peak(parser, 1)->type == TOKEN_SEMICOLON) {		
		ast->term = parse_term(parser);
		return ast;
	}

	parser_eat(parser);
	
	if (parser->current_token->type == TOKEN_ID) {
		// Errorm malformed expression (consequitive IDs)
		puts("ERROR: INVALID EXPRESSION");
		exit(1);
	}	

	return ast;
}

ast_t* parse_term(parser_t* parser) {
	ast_t* ast = init_ast(AST_TERM);

	ast->factor = parse_factor(parser);
	
	return ast;
}


ast_t* parse_factor(parser_t* parser) {
	ast_t* ast = init_ast(AST_FACTOR);

	ast->id = parse_id(parser);

	return ast;
}

char* parse_id(parser_t* parser) {
	size_t len = strlen(parser->current_token->value);
	char* id = malloc(len+1 * sizeof(char));

	strncpy(id, parser->current_token->value, len);
	id[len] = 0;

	return id;
}


ast_t* parser_parse(token_t** token_list) {
	ast_t* ast_compound = init_ast(AST_COMPOUND);
	parser_t* parser = init_parser(token_list);	
	
	ast_compound->statement = parse_statement(parser);		
		
	puts(ast_compound->statement->expression->term->factor->id);

	free(parser);
	return ast_compound;
}

