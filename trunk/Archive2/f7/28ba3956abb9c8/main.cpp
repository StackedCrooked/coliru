/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int    grep(char*, FILE*, char*);
int	match(char*, char*);
int	matchhere(char*, char*);
int	matchstar(int, char*, char*);

/* grep main: search for regexp in files */
int main(int argc, char *argv[])
{
	int i, nmatch;
	FILE *f;

	//setprogname("grep");
	if (argc < 2)
		puts("usage: grep regexp [file ...]");
	nmatch = 0;
	if (argc == 2) {
		if (grep(argv[1], stdin, NULL))
			nmatch++;
	} else {
		for (i = 2; i < argc; i++) {
			f = fopen(argv[i], "r");
			if (f == NULL) {
				printf("can't open %s:", argv[i]);
				continue;
			}
			if (grep(argv[1], f, argc>3 ? argv[i] : NULL) > 0)
				nmatch++;
			fclose(f);
		}
	}
	return nmatch == 0;
}

/* grep: search for regexp in file */
int grep(char *regexp, FILE *f, char *name)
{
	int n, nmatch;
	char buf[BUFSIZ];

	nmatch = 0;
	while (fgets(buf, sizeof buf, f) != NULL) {
		n = strlen(buf);
		if (n > 0 && buf[n-1] == '\n')
			buf[n-1] = '\0';
		if (match(regexp, buf)) {
			nmatch++;
			if (name != NULL)
				printf("%s:", name);
			printf("%s\n", buf);
		}
	}
	return nmatch;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return 1;
	if (regexp[1] == '*')
		return matchstar(regexp[0], regexp+2, text);
	if (regexp[0] == '$' && regexp[1] == '\0')
		return *text == '\0';
	if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
		return matchhere(regexp+1, text+1);
	return 0;
}

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text)
{
	if (regexp[0] == '^')
		return matchhere(regexp+1, text);
	do {	/* must look even if string is empty */
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
	do {	/* a * matches zero or more instances */
		if (matchhere(regexp, text))
			return 1;
	} while (*text != '\0' && (*text++ == c || c == '.'));
	return 0;
}