#include "include/IO.h"

#include <stdio.h>
#include <stdlib.h>

char* read_file(char* filename){
	FILE* fptr = fopen(filename, "r");

	if(fptr == NULL){
		printf("ERROR: File does not exist.\n");
		exit(1);
	}else{
		fseek(fptr, 0, SEEK_END);
		long fsize = ftell(fptr);
		fseek(fptr, 0, SEEK_SET);

		char* buff = malloc(fsize + 1);
		fread(buff, fsize, 1, fptr);
		fclose(fptr);

		buff[fsize] = 0;
		return buff;
	}
	return "Error";
}
