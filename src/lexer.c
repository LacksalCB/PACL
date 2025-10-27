#include "../include/lexer.h"
#include "../include/token.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// PACL LEXER

lexer_t* init_lexer(char* buff){
	lexer_t* lexer = malloc(1 * sizeof(struct LEXER_STRUCT));

	lexer->contents = strdup(buff);
	lexer->c = buff[0];
	lexer->i = 0;
	lexer->line = 0;
	lexer->linech = 0;
	return lexer;
}

lexer_t* lexer_eat(lexer_t* lexer){
	lexer->i++;
	lexer->c = lexer->contents[lexer->i];
	lexer->linech++;
	return lexer;
}

char* symbol_to_string(lexer_t* lexer){
	char* str = malloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = 0;
	lexer_eat(lexer);
	return str;
}

char lexer_peak(lexer_t* lexer){
	return lexer->contents[lexer->i+1];
}

lexer_t* lexer_skip(lexer_t* lexer){
	while(lexer->c != 10){
		lexer_eat(lexer);
	}
	lexer_eat(lexer);
	lexer_eat(lexer);
	lexer->line++;
	lexer->linech = 0;
	return lexer;
}

token_t* lexer_get_token(lexer_t* lexer){
	const char* sep = " \n\t(;:{";
	size_t len = strcspn(lexer->contents + lexer->i, sep);
	char* tok = strndup(lexer->contents+lexer->i, len);
	tok[len] = '\0';
	lexer->i += len-1;
	lexer_eat(lexer);
	return isdigit(tok[0]) ? init_token(tok, TOKEN_NUM) : init_token(tok, TOKEN_ID); // Returns ID if alphabet chars, returns num (i.e. const literal) if digit
}

token_t* lexer_collect_string(lexer_t* lexer){
	char* str = malloc(1 * sizeof(char));
	str[0] = '\0';
	if(lexer->c == '\"'){
		lexer_eat(lexer);
		while(lexer->c != '\"'){
			str = realloc(str, strlen(str)+2*sizeof(char));
			char* ch = malloc(2 * sizeof(char));
			sprintf(ch, "%c", lexer->c);
			strcat(str, ch);
			lexer_eat(lexer);
			free(ch);
		}
	}

	lexer_eat(lexer);
	return init_token(str, TOKEN_ID);
}

token_t* lexer_advance(lexer_t* lexer){
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
		case 0: return NULL; 
		default: printf("Invalid token line %d, %d: \"%c\"", lexer->line, lexer->linech, lexer->c);exit(1);
	}
	return (void*)0;
}

token_t** lexer_tokenize(char* buff, int* token_count) {
	*token_count = 0;
	token_t** token_list = malloc(1 * sizeof(struct TOKEN_STRUCT*));
	lexer_t* lexer = init_lexer(buff);

	FILE* fptr = fopen("tokens.txt", "r");	

	while (lexer->c != 0) {
		token_list = realloc(token_list, (*token_count+1) * sizeof(token_t*));
		token_list[*token_count] = lexer_advance(lexer);

		fwrite(&token_list[*token_count]->type, sizeof(int), 1, fptr);
		puts(token_list[*token_count]->value);
		fwrite(token_list[*token_count]->value, sizeof(char), strlen(token_list[*token_count]->value), fptr);
		
		*token_count += 1;	
	}

	fclose(fptr);

	token_t* end_token = init_token(NULL, TOKEN_EOF);
	token_list = realloc(token_list, (*token_count+1) * sizeof(token_t*));
	token_list[*token_count] = end_token;

	free(lexer->contents);
	free(lexer);
	return token_list;
}

