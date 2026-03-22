#include "../include/parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define AST_TYPE(token_type)  (AST_VAR + (token_type) - TOKEN_ID)

// Thank you chatgpt for this print function
void print_ast(ast_t* ast, int depth, const char* side) {
    if (!ast) return;

    for (int i = 0; i < depth; i++) printf("  ");
    if (side) printf("%s", side);

    switch(ast->type) {
        case AST_VAR:
            printf("AST_VAR (Value = '%s')\n", ast->value);
            return;
        case AST_NUM:
            printf("AST_NUM (Value = '%s')\n", ast->value);
            return;
        case AST_COMPOUND:
            puts("COMPOUND ->");
            for (int i = 0; ast->children && ast->children[i]; i++) {
                print_ast(ast->children[i], depth+1, NULL);
            }
            return;
        default:
            // For operator nodes, use value string if present
            printf("%s ->\n", ast->value ? ast->value : "UNKNOWN");
            break;
    }

    // Recurse on L and R if they exist
    if (ast->L) print_ast(ast->L, depth+1, "L: ");
    if (ast->R) print_ast(ast->R, depth+1, "R: ");
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

	if (parser_peak(parser, 1)->type == TOKEN_EQ){
		ast = parse_assignment(parser); 
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
	
	parser_eat(parser); //Eat semi

	return ast;
}

ast_t* parse_expression(parser_t* parser, ast_t* ast) {
	ast->L = init_child(AST_TYPE(parser->current_token->type));
	ast->L->value = parse_tok(parser);
	parser_eat(parser);

	parser_eat(parser); // Eat op

	if (parser_peak(parser,1)->type == TOKEN_SEMICOLON) {
		ast->R = init_child(AST_TYPE(parser->current_token->type));
		ast->R->value = parse_tok(parser);
		parser_eat(parser);
		return ast;
		
	}	

	ast->R = parse_expressions(parser);

	return ast;
}

// Need to insert precedence and term/factor logic here
ast_t* parse_expressions(parser_t* parser) {
	ast_t* ast = NULL;

	int op = parser_peak(parser,1)->type;

	switch(op) {
		case TOKEN_PLUS:
			ast = init_child(AST_EXPRESSION_ADD);
			ast->value = "ADDITION EXPRESSION\'+\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_MINUS:
			ast = init_child(AST_EXPRESSION_SUB);
			ast->value = "SUBTRACTION EXPRESSION \'-\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_ASTERISK:
			ast = init_child(AST_EXPRESSION_MUL);
			ast->value = "MULTIPLICATION EXPRESSION \'*\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_SLASH:
			ast = init_child(AST_EXPRESSION_DIV);
			ast->value = "DIVISION EXPRESSION \'/\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_MOD:
			ast = init_child(AST_EXPRESSION_MOD);
			ast->value = "DIVISION EXPRESSION \'%\'";
			ast = parse_expression(parser, ast);
			break;
		default:
			puts("ERROR: INVALID OPERATOR"); // TODO: make this good
			break;
	}

	return ast;
}

ast_t* parse_assignment(parser_t* parser) {
	ast_t* ast = init_child(AST_STATEMENT_ASSIGNMENT);
	ast->value = "ASSIGNMENT STATEMENT \'=\'";
	
	// L Value check handled in statement	
	ast->L = init_child(AST_VAR);
	ast->L->value = parse_tok(parser);
	parser_eat(parser);	

	parser_eat(parser); // eat op
	
	token_t* R_tok = parser->current_token;
	if (R_tok->type != TOKEN_NUM) {
		// Error, malformed Expression (not num)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected num \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_NUM, parser->current_token->type);
		exit(1);
	}

	if (parser_peak(parser,1)->type == TOKEN_SEMICOLON) {
		ast->R = init_child(AST_NUM);
		ast->R->value = parse_tok(parser);	
		return ast;
	}

	ast->R = parse_expressions(parser);

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
	ast_t* ast = init_child(AST_COMPOUND);
	ast->value = "ROOT";
	ast->children = init_compound(1); 
	
	parser_t* parser = init_parser(token_list);	

	ast->children[0] = parse_statement(parser);

	puts("AST:");
	print_ast(ast, 0, NULL);

	free(parser);
	return ast;
}

