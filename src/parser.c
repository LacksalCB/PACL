#include "../include/parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// I already know this is bad, ill make it good one day
void print_ast(ast_t* ast) {
	unsigned int curr_type = ast->type;

	switch(curr_type) {
		case AST_COMPOUND:
			print_ast(ast->statement);
			break;	
		case AST_STATEMENT:
			print_ast(ast->expression);
			break;
		case AST_EXPRESSION:
			print_ast(ast->term);
			break;
		case AST_TERM:
			print_ast(ast->factor);
			break;
		case AST_FACTOR:
			puts(ast->id);
			puts(ast->op);
			puts(ast->num);
			break;
	};
}

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
	return 0;
}

token_t* parser_peak(parser_t* parser, int peak_dist) {
	return parser->tokens[parser->current_token_index+peak_dist];
}

ast_t* parse_statement(parser_t* parser) {
	ast_t* ast = init_ast(AST_STATEMENT);
	ast->expression = parse_expression(parser);		

	return ast;
}

ast_t* parse_expression(parser_t* parser) {
	ast_t* ast = init_ast(AST_EXPRESSION);
	ast->term = parse_term(parser);
	
	parser_eat(parser); //Eat semi
	
	if (parser->current_token->type != TOKEN_SEMICOLON) {
		// Errorm malformed expression (consequitive IDs)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_ID, parser->current_token->type);
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

	token_t* L = parser->current_token;
	if (L->type != TOKEN_ID) {
		// Error, malformed Expression (leading op)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_ID, parser->current_token->type);
		exit(1);
	}
	ast->id = parse_tok(parser);

	parser_eat(parser);	
	token_t* OP = parser->current_token;
	if (OP->type != TOKEN_EQ) {
		// Error, malformed Expression (not =)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_ID, parser->current_token->type);
		exit(1);
	}
	ast->op = parse_tok(parser);

	parser_eat(parser);
	token_t* R = parser->current_token;
	if (R->type != TOKEN_NUM) {
		// Error, malformed Expression (not num)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_ID, parser->current_token->type);
		exit(1);
	}
	ast->num = parse_tok(parser);

	return ast;
}

char* parse_tok(parser_t* parser) {
	size_t len = strlen(parser->current_token->value);
	char* tok = malloc(len + 1);

	strncpy(tok, parser->current_token->value, len);
	tok[len] = 0;

	return tok;
}

ast_t* parser_parse(token_t** token_list) {
	ast_t* ast_compound = init_ast(AST_COMPOUND);
	parser_t* parser = init_parser(token_list);	
	
	ast_compound->statement = parse_statement(parser);		
	
	//print_ast(ast_compound);

	free(parser);
	return ast_compound;
}

