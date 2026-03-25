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

char lexer_peak(lexer_t* lexer, int dist){
	return lexer->contents[lexer->i+dist];
}

lexer_t* lexer_skip(lexer_t* lexer){
	while(lexer->c != 10){
		lexer_eat(lexer);
	}
	lexer_eat(lexer);
	lexer->line++;
	lexer->linech = 0;
	return lexer;
}

token_t* lexer_get_token(lexer_t* lexer){
	const char* sep = " \n\t(;:{";
	size_t len = strcspn(lexer->contents + lexer->i, sep);
	char* tok = strndup(lexer->contents+lexer->i, len);
	tok[len] = 0;
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

char* symbol_to_string(lexer_t* lexer){
	char* str = malloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = 0;
	lexer_eat(lexer);
	return str;
}

char* complex_symbol_to_string(lexer_t* lexer, int len) {
	char* str = malloc(len+1 * sizeof(char));

	for (int i = 0; i < len; i++) {
		str[i] = lexer->c;
		lexer_eat(lexer);
	}
	str[len] = 0;
	return str;
}

token_t* lexer_collect_symbol(lexer_t* lexer) {
	switch(lexer->c){

// Single Character Cases

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
		case '?': return init_token(symbol_to_string(lexer), TOKEN_QUESTION);
		case '_': return init_token(symbol_to_string(lexer), TOKEN_UNDERSCORE);

// Two character Cases		

		case '=': 
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_IS); }	
			return init_token(symbol_to_string(lexer), TOKEN_EQ);
		case '*': 	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_MULEQ); }	
			return init_token(symbol_to_string(lexer), TOKEN_ASTERISK);
		case '/': 
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_DIVEQ); }	
			return init_token(symbol_to_string(lexer), TOKEN_SLASH);
		case '%': 	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_MODEQ); }	
			return init_token(symbol_to_string(lexer), TOKEN_MOD);
		case '!':	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_NE); }	
			return init_token(symbol_to_string(lexer), TOKEN_BANG);
		case '^': 
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_BWXOREQ); }	
			return init_token(symbol_to_string(lexer), TOKEN_CARET);

// Multi-Use cases
		case '&': 
			if (lexer_peak(lexer, 1) == '&') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_AND); }	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_BWANDEQ); }	
			return init_token(symbol_to_string(lexer), TOKEN_AMPERSAND);
		case '|': 	
			if (lexer_peak(lexer, 1) == '|') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_OR); }	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_BWOREQ); }	
			return init_token(symbol_to_string(lexer), TOKEN_BAR);
		case '-': 	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_SUBEQ); }
			if (lexer_peak(lexer, 1) == '-') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_DEC); }	
			return init_token(symbol_to_string(lexer), TOKEN_MINUS);
		case '+': 
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_ADDEQ); }
			if (lexer_peak(lexer, 1) == '+') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_INC); }	
			return init_token(symbol_to_string(lexer), TOKEN_PLUS);
		case '<': 	
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_LE); }	
			if (lexer_peak(lexer, 1) == '<' && lexer_peak(lexer, 2) == '=') { return init_token(complex_symbol_to_string(lexer, 3), TOKEN_BWLSEQ); }
			if (lexer_peak(lexer, 1) == '<') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_BWLS); }	
			return init_token(symbol_to_string(lexer), TOKEN_LT);
		case '>':
			if (lexer_peak(lexer, 1) == '=') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_GE); }	
			if (lexer_peak(lexer, 1) == '>' && lexer_peak(lexer, 2) == '=') { return init_token(complex_symbol_to_string(lexer, 3), TOKEN_BWRSEQ); }
			if (lexer_peak(lexer, 1) == '>') { return init_token(complex_symbol_to_string(lexer, 2), TOKEN_BWRS); }	
			return init_token(symbol_to_string(lexer), TOKEN_GT);
		case 0: return init_token("", TOKEN_EOF);

		default: printf("Invalid token line %d, %d: \"%c\"\n", lexer->line, lexer->linech, lexer->c);exit(1);
	}

	// Should be impossible
	return NULL;
}

token_t* lexer_advance(lexer_t* lexer){
	while(lexer->c == 32 || lexer->c == 9 || lexer->c == 10){ // space, tab, newline
		if(lexer->c == 10){
			lexer->linech = 0;
			lexer->line++;
		}
		lexer_eat(lexer);
	}

	if(lexer->c == '/' && lexer_peak(lexer, 1) == '/'){
		lexer_skip(lexer);
		lexer->line++;
	}
		
	if(lexer->c == '\"' || lexer->c == '\''){
		return lexer_collect_string(lexer);	
	}

	if(isalnum(lexer->c)){
		return lexer_get_token(lexer);
	}

	return lexer_collect_symbol(lexer);
}

token_t** lexer_tokenize(char* buff, int* token_count, int* line_count) {
	*token_count = 0;
	token_t** token_list = malloc(1 * sizeof(struct TOKEN_STRUCT*));
	lexer_t* lexer = init_lexer(buff);

	while (lexer->c != 0) {
		token_list = realloc(token_list, (*token_count+1) * sizeof(token_t*));
		// TODO: Null return handling
		token_list[*token_count] = lexer_advance(lexer);

		*token_count += 1;	
	}

	token_t* end_token = init_token(NULL, TOKEN_EOF);
	token_list = realloc(token_list, (*token_count+1) * sizeof(token_t*));
	token_list[*token_count] = end_token;

	*line_count = lexer->line;

	free(lexer->contents);
	free(lexer);
	return token_list;
}

