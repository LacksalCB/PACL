#ifndef PACL_LEXER_H
#define PACL_LEXER_H

#include "token.h"

typedef struct LEXER_STRUCT{
	char* contents;
	char c;
	int i;
	int line;
	int linech;
}lexer_t;

lexer_t* init_lexer(const char* buff);

lexer_t* lexer_eat(lexer_t* lexer);
char* to_string(lexer_t* lexer);
char* symbol_to_string(lexer_t* lexer);
char lexer_peak(lexer_t* lexer);
lexer_t* lexer_skip(lexer_t* lexer);
token_t* lexer_get_token(lexer_t* lexer);
token_t* lexer_collect_string(lexer_t* lexer);

token_t* lexer_advance(lexer_t* lexer);

token_t** tokenize(const char* buff);

#endif /* PACL_LEXER_H */
