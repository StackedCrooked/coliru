#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
    char str[] = "asbd0:sdsd1:ssdwdwd2";
	int tokens = 0;
	int i = 0;
	char **res = NULL;

	char *token = strtok(str, ":");
	for (tokens = 1; token; ++tokens) {
		res = realloc(res, tokens *sizeof(*res));		
		res[tokens - 1] = malloc(strlen(token) + 1);
		strncpy(res[tokens - 1], token, strlen(token) + 1);
		token = strtok(NULL, ":");
	}

	for (i = 0; i<tokens-1; ++i){
		puts(res[i]);
	}
	return 0;
}