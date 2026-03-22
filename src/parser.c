#include "../include/parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// I already know this is bad, ill make it good one day
void print_ast(ast_t* ast) {
	unsigned int curr_type = ast->type;

	switch(curr_type) {
		case AST_ROOT:
			puts("ROOT ->");
			print_ast(ast->children[0]);
			break;	
		case AST_STATEMENT_ASSIGNMENT:
			puts("  +-> ASSIGNMENT STATEMENT \'=\'->");
			print_ast(ast->L);
			print_ast(ast->R);
			break;
		case AST_EXPRESSION_ADD:
			puts("   EXPRESSION ->");
			break;
		case AST_VAR:	
			printf("    +-> L: AST_VAR (Value = \'%s\'\n", ast->value);
			break;
		case AST_NUM:
			printf("    +-> R: AST_NUM (Value = \'%s\'\n", ast->value);
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
	ast_t* ast = NULL;

	if (parser->current_token->type != TOKEN_ID) {
		// Has to be a token 
		printf("ERROR, INVALID STATEMENT: %s\n", parser->current_token->value);
		return NULL; // Handle this one day
	}

	if (!strcmp(parser->current_token->value, "if")) {
		ast = init_child(AST_STATEMENT_IF);
	}	
	if (!strcmp(parser->current_token->value, "for")) {
		ast = init_child(AST_STATEMENT_FOR);
	}
	if (!strcmp(parser->current_token->value, "while")) {
		ast = init_child(AST_STATEMENT_WHILE);
	}
	if (!strcmp(parser->current_token->value, "return")) {
		ast = init_child(AST_STATEMENT_RETURN);
	}
	if (parser_peak(parser, 1)->type == TOKEN_EQ){
		ast = parse_assignment(parser); 	
	}

	return ast;
}

ast_t* parse_expression(parser_t* parser) {
	ast_t* ast = init_child(AST_EXPRESSION_ADD);
	
	parser_eat(parser); //Eat semi
	
	if (parser->current_token->type != TOKEN_SEMICOLON) { 
		// Error malformed expression (consequitive IDs)
		printf("ERROR, INVALID EXPRESSION (expected semicolon): %s\nExpected \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_SEMICOLON, parser->current_token->type);
		exit(1);
	}	

	return ast;
}

ast_t* parse_assignment(parser_t* parser) {
	ast_t* ast = init_child(AST_STATEMENT_ASSIGNMENT);

	token_t* L_tok = parser->current_token;
	if (L_tok->type != TOKEN_ID) {
		// Error, malformed Expression (leading op)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected id \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_ID, parser->current_token->type);
		exit(1);
	}
	ast->L = init_child(AST_VAR);
	ast->L->value = parse_tok(parser);
	parser_eat(parser);	

	parser_eat(parser);

	token_t* R_tok = parser->current_token;
	if (R_tok->type != TOKEN_NUM) {
		// Error, malformed Expression (not num)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected num \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_NUM, parser->current_token->type);
		exit(1);
	}
	ast->R = init_child(AST_NUM);
	ast->R->value = parse_tok(parser);

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
	ast_t* ast = init_child(AST_ROOT);
	ast->children = init_compound(); 
	
	parser_t* parser = init_parser(token_list);	

	ast->children[0] = parse_statement(parser);	

	puts("AST:");
	print_ast(ast);

	free(parser);
	return ast;
}

