#include "include/IO.h"
#include "include/parser.h"

#include <stdio.h>

int main(int argc, char** argv){
	lexer_T* lexer = init_lexer(read_file(argv[1]));
	parser_T* parser = init_parser(lexer);
	ast_T* root_node = parser_parse_statements(parser);
	
	return 0;
}
