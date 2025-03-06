#include "../include/token.h"

#include <stdlib.h>

token_t* init_token(char* str, int type){
	token_t* token = malloc(1*sizeof(struct TOKEN_STRUCT));
	token->value = str;
	token->type = type;
	return token;
}
