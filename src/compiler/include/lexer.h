#ifndef PACL_LEXER_H
#define PACL_LEXER_H

#include "token.h"

typedef struct LEXER_STRUCT{
	char* contents;
	char c;
	int i;
	int line;
	int linech;
}lexer_T;

lexer_T* init_lexer(char* buff);

lexer_T* lexer_eat(lexer_T* lexer);
char* to_string(lexer_T* lexer);
char* symbol_to_string(lexer_T* lexer);
char lexer_peak(lexer_T* lexer);
lexer_T* lexer_skip(lexer_T* lexer);
token_T* lexer_get_token(lexer_T* lexer);
token_T* lexer_collect_string(lexer_T* lexer);

token_T* lexer_advance(lexer_T* lexer);


#endif /* PACL_LEXER_H */
