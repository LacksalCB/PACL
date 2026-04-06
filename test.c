#include <stdio.h>

int main(int argc, char** argv){
    printf("%s", "Hello World!\n");

	int y = 0;
	int l = 1;
	int x = y++ * 9 + 1 << 2 < 3 == 4 & 5 ^ 6 | 7 && 8 || y == 1 ? 2 : 3, z = --l;

    return 0;
}
