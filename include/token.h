#ifndef PACL_TOKEN_H
#define PACL_TOKEN_H

typedef struct TOKEN_STRUCT {
	enum token_type{
		// TOKEN_SIMPLE_SYMBOLS
		TOKEN_LPAREN, 		// 0 	(
		TOKEN_RPAREN, 		// 1 	)
		TOKEN_LBRACKET, 	// 2 	[
		TOKEN_RBRACKET, 	// 3 	]
		TOKEN_LBRACE, 		// 4 	{
		TOKEN_RBRACE, 		// 5 	}
		TOKEN_COMMA, 		// 6 	,
		TOKEN_PERIOD, 		// 7 	.
		TOKEN_COLON, 		// 8 	:
		TOKEN_SEMICOLON, 	// 9 	;
		TOKEN_EQ, 			// 10 	=
		TOKEN_UNDERSCORE, 	// 11 	_
		TOKEN_QUESTION, 	// 12 	?
		TOKEN_GT, 			// 13 	>
		TOKEN_LT, 			// 14 	<
		TOKEN_BANG, 		// 15 	!
		TOKEN_PLUS, 		// 16 	+	
		TOKEN_MINUS, 		// 17 	-
		TOKEN_ASTERISK, 	// 18 	*
		TOKEN_SLASH, 		// 19 	/
		TOKEN_MOD, 			// 20 	%
		TOKEN_AMPERSAND, 	// 21 	&
		TOKEN_CARET, 		// 22 	^
		TOKEN_BAR, 			// 23  	|

		// TOKEN_COMPLEX_SYMBOLS
		TOKEN_BWLS, 		// 24 	<<
		TOKEN_BWRS, 		// 25 	>>
		TOKEN_GE, 			// 26 	>=
		TOKEN_LE, 			// 27 	<=
		TOKEN_IS, 			// 28 	==
		TOKEN_NE, 			// 29 	!=
		TOKEN_AND, 			// 30  	&&
		TOKEN_OR, 			// 31 	||
		TOKEN_ADDEQ, 		// 32 	+=
		TOKEN_SUBEQ, 		// 33 	-=
		TOKEN_MULEQ, 		// 34 	*=
		TOKEN_DIVEQ,		// 35 	/=
		TOKEN_MODEQ, 		// 36 	%=
		TOKEN_BWANDEQ, 		// 37 	&=
		TOKEN_BWXOREQ, 		// 38 	^=
		TOKEN_BWOREQ, 		// 39 	|=
		TOKEN_BWLSEQ, 		// 40 	<<=
		TOKEN_BWRSEQ, 		// 41 	>>=
		TOKEN_INC, 			// 42 	++
		TOKEN_DEC, 			// 43 	--

		// TOKEN IDENTIFIERS
		TOKEN_ID, 			// 44  	Some string a-zA-X_0-9
		TOKEN_NUM,  		// 45 	Digit 0-9

		// EOF
		TOKEN_EOF 			// 46 	' '
	}type;
	char* value;
}token_t;

token_t* init_token(char* str, int type);

#endif /* PACL_TOKEN_H */
