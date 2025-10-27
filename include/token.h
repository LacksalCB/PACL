#ifndef PACL_TOKEN_H
#define PACL_TOKEN_H

typedef struct TOKEN_STRUCT {
	enum token_type{
		// TOKEN SYMBOLS
		TOKEN_LPAREN, 		// 0
		TOKEN_RPAREN, 		// 1
		TOKEN_LBRACKET, 	// 2
		TOKEN_RBRACKET, 	// 3
		TOKEN_LBRACE, 		// 4
		TOKEN_RBRACE, 		// 5
		TOKEN_COMMA, 		// 6
		TOKEN_PERIOD, 		// 7
		TOKEN_COLON, 		// 8
		TOKEN_SEMICOLON, 	// 9
		TOKEN_EQ, 			// 10
		TOKEN_QUESTION, 	// 11
		TOKEN_LT, 			// 12
		TOKEN_GT, 			// 13
		TOKEN_UNDERSCORE, 	// 14
		TOKEN_ASTERISK, 	// 15
		TOKEN_MINUS, 		// 16
		TOKEN_PLUS, 		// 17
		TOKEN_SLASH, 		// 18
		TOKEN_MOD, 			// 19

		// TOKEN IDENTIFIERS
		TOKEN_ID, 		// 20
		TOKEN_NUM,  	// 21

		// EOF
		TOKEN_EOF 		// 22
	}type;
	char* value;
}token_t;

token_t* init_token(char* str, int type);

#endif /* PACL_TOKEN_H */
