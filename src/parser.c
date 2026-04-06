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
			free(ast);
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
	if (parser->current_token->type == TOKEN_EOF) {
		free(parser->current_token);
		return NULL;
	}

	ast_t* ast = NULL;

	if (parser->current_token->type != TOKEN_ID) {
		// Has to be a token 
		printf("ERROR, INVALID STATEMENT: \'%s\', CANNOT BE TYPE \'%d\'\n", parser->current_token->value, parser->current_token->type);
		return NULL; // Handle this one day
	}
	
	if (parser_peak(parser, 1)->type == TOKEN_EQ || (parser_peak(parser, 1)->type >= 30 && parser_peak(parser, 1)->type <= 41)){	
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
	// Parse L
	ast->L = init_child(AST_TYPE(parser->current_token->type));
	ast->L->value = parse_tok(parser);
	parser_eat(parser);

	parser_eat(parser); // Eat op

	// Parse R
	if (parser_peak(parser, 1)->type == TOKEN_SEMICOLON) {
		ast->R = init_child(AST_TYPE(parser->current_token->type));
		ast->R->value = parse_tok(parser);
		parser_eat(parser);
		return ast;
		
	} 	

	ast->R = parse_expressions(parser);

	return ast;
}

// y = 1 * 2 + 3
// ADD
//  Mul
//   1
//   2
//  3


// x = 1 + 2 * 3
// ADD 
// 	1
// 	Mul
// 	  2
// 	  3


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
			ast->value = "REMAINDER EXPRESSION \'%\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_CARET:
			ast = init_child(AST_EXPRESSION_XOR);
			ast->value = "XOR EXPRESSION \'^\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_AMPERSAND:
			ast = init_child(AST_EXPRESSION_AND);
			ast->value = "AND EXPRESSION \'&\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_BAR:
			ast = init_child(AST_EXPRESSION_OR);
			ast->value = "OR EXPRESSION \'|\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_BWLS:
			ast = init_child(AST_EXPRESSION_BWLS);
			ast->value = "BITWISE LEFT SHIFT EXPRESSION \'<<\'";
			ast = parse_expression(parser, ast);
			break;
		case TOKEN_BWRS:
			ast = init_child(AST_EXPRESSION_BWRS);
			ast->value = "BITWISE RIGHT SHIFT EXPRESSION \'>>\'";
			ast = parse_expression(parser, ast);
			break;
		default:
			printf("ERROR: INVALID OPERATOR \'%s\' OF TYPE \'%d\'\n", parser->current_token->value, op); 
			break;
	}

	return ast;
}

char* get_op(token_t* token) {
	int i = 0;
	char* op = malloc(3 * sizeof(char));
	while (token->value[i] != '=') {
		op[i] = token->value[i];
		i++;
	}
	free(token->value);
	op[i] = 0;
	return op;
}

ast_t* parse_assignment(parser_t* parser) {
	ast_t* ast = init_child(AST_STATEMENT_ASSIGNMENT);
	ast->value = "ASSIGNMENT STATEMENT \'=\'";
	
	// L Value check handled in statement	
	ast->L = init_child(AST_VAR);
	ast->L->value = parse_tok(parser);

	token_t* peak = parser_peak(parser,1);
	if (peak->type == TOKEN_EQ) {
		parser_eat(parser);
		parser_eat(parser);
	} else {
		peak->value = get_op(peak);
		peak->type -= 16;
	}
	
	token_t* R_tok = parser->current_token;
	if (R_tok->type != TOKEN_NUM && R_tok->type != TOKEN_ID) {
		// Error, malformed Expression (Must be Num or Var after =)
		printf("ERROR, INVALID EXPRESSION: %s\nExpected NUM or ID \'%d\', got \'%d\'\n", parser->current_token->value, TOKEN_NUM, parser->current_token->type);
		exit(1);
	}

	if (parser_peak(parser,1)->type == TOKEN_SEMICOLON) {
		ast->R = init_child(AST_NUM);
		ast->R->value = parse_tok(parser);	
		parser_eat(parser);
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

ast_t* parser_parse(token_t** token_list, int len) {
	ast_t* ast = init_child(AST_COMPOUND);
	ast->value = "ROOT";
	ast->children = init_compound(len); 
	
	parser_t* parser = init_parser(token_list);	

	for (int i = 0; i < len-2; i++) {
		ast->children[i] = parse_statement(parser);
	}

	print_ast(ast, 0, NULL);

	free(parser);
	return ast;
}

