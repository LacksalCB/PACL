#include "include/lexer.h"

#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// PACL LEXER

lexer_T* init_lexer(char* buff){
	lexer_T* lexer = malloc(1 * sizeof(struct LEXER_STRUCT));

	lexer->contents = buff;
	lexer->c = buff[0];
	lexer->i = 0;
	lexer->line = 0;
	lexer->linech = 0;
	return lexer;
}

lexer_T* lexer_eat(lexer_T* lexer){
	lexer->i++;
	lexer->c = lexer->contents[lexer->i];
	lexer->linech++;
	return lexer;
}

char* to_string(lexer_T* lexer){
	char* str = malloc(1 * sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return str;
}

char* symbol_to_string(lexer_T* lexer){
	char* str = malloc(1*sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	lexer_eat(lexer);
	return str;
}

char lexer_peak(lexer_T* lexer){
	return lexer->contents[lexer->i+1];
}

lexer_T* lexer_skip(lexer_T* lexer){
	while(lexer->c != 10){
		lexer_eat(lexer);
	}
	lexer_eat(lexer);
	lexer_eat(lexer);
	lexer->line++;
	lexer->linech=0;
	return lexer;
}

token_T* lexer_get_token(lexer_T* lexer){
	char* str = malloc(1*sizeof(char));
	str[0] = '\0';
	while(isalnum(lexer->c)){
		str = realloc(str, (strlen(str)+1*sizeof(char)));
		str = strcat(str, to_string(lexer));
		lexer_eat(lexer);
	}

	return init_token(str, TOKEN_ID);
}

token_T* lexer_collect_string(lexer_T* lexer){
	char* str = malloc(1*sizeof(char));
	str[0] = '\0';
	if(lexer->c == '\''){
		lexer_eat(lexer);
		while(lexer->c != '\''){
			str = realloc(str, strlen(str)+2*sizeof(char));
			str = strcat(str, to_string(lexer));
			lexer_eat(lexer);
		}
	}else if(lexer->c == '\"'){
		lexer_eat(lexer);
		while(lexer->c != '\"'){
			str = realloc(str, strlen(str)+2*sizeof(char));
			str = strcat(str, to_string(lexer));
			lexer_eat(lexer);
		}
	}

	lexer_eat(lexer);
	return init_token(str, TOKEN_ID);
}

token_T* lexer_advance(lexer_T* lexer){
//	printf("%c\n", lexer->c);
	while(lexer->c == 32 || lexer->c == 9 || lexer->c == 10){
		if(lexer->c == 10){
			lexer->linech = 0;
		}
		lexer_eat(lexer);
	}

	if(lexer->c == '/' && lexer_peak(lexer) == '/'){
		lexer_skip(lexer);
	}
		
	if(lexer->c == '\"' || lexer->c == '\''){
		return lexer_collect_string(lexer);	
	}

	if(isalnum(lexer->c)){
		return lexer_get_token(lexer);
	}

	if(!isalnum(lexer->c)){
		switch(lexer->c){
			case '(': return init_token(symbol_to_string(lexer), TOKEN_LPAREN);
			case ')': return init_token(symbol_to_string(lexer), TOKEN_RPAREN);
			case '{': return init_token(symbol_to_string(lexer), TOKEN_LBRACE);
			case '}': return init_token(symbol_to_string(lexer), TOKEN_RBRACE);
			case '[': return init_token(symbol_to_string(lexer), TOKEN_LBRACKET);
			case ']': return init_token(symbol_to_string(lexer), TOKEN_RBRACKET);
			case ',': return init_token(symbol_to_string(lexer), TOKEN_COMMA);
			case '.': return init_token(symbol_to_string(lexer), TOKEN_PERIOD);
			case ':': return init_token(symbol_to_string(lexer), TOKEN_COLON);
			case ';': return init_token(symbol_to_string(lexer), TOKEN_SEMICOLON);
			case '=': return init_token(symbol_to_string(lexer), TOKEN_EQ);
			case '?': return init_token(symbol_to_string(lexer), TOKEN_QUESTION);
			case '<': return init_token(symbol_to_string(lexer), TOKEN_LT);	
			case '>': return init_token(symbol_to_string(lexer), TOKEN_GT);
			case '_': return init_token(symbol_to_string(lexer), TOKEN_UNDERSCORE);
			case '*': return init_token(symbol_to_string(lexer), TOKEN_ASTERISK);
			case '-': return init_token(symbol_to_string(lexer), TOKEN_MINUS);
			case '+': return init_token(symbol_to_string(lexer), TOKEN_PLUS);
			case '/': return init_token(symbol_to_string(lexer), TOKEN_SLASH);
			case '%': return init_token(symbol_to_string(lexer), TOKEN_MOD);
			case 0: exit(EXIT_SUCCESS);
			default:printf("Invalid token line %d, %d: \"%c\"", lexer->line, lexer->linech, lexer->c);exit(1);
		}
	}
	return (void*)0;
}
