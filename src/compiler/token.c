#include "include/token.h"

#include <stdlib.h>

token_T* init_token(char* str, int type){
	token_T* token = malloc(1*sizeof(char(struct TOKEN_STRUCT)));
	token->value = str;
	token->type = type;
	return token;
}
