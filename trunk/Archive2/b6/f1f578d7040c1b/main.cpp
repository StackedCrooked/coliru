#include <stdio.h>

#define false 0;
#define true 1;

int main()
{
    /*declare variables*/
	int c;
	int size = 0;
	int x;
	char string[141];
	int index = 0;
	char prog[] = "programming";
	char cpp[] = "cpp";
	char nba[] = "nba";
	char yolo[] = "yolo";
	int match = 1;
	int word = -1;

	while((c = getchar()) != EOF && size < 140)
	{
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			string[size++] = c;

	}

	string[size] = '\0';

	for(x = 0; x < size && match; x++, index++)
	{
		if(index < 11 && tolower(string[x]) == prog[index])
		{
			if(word < 0)
				word = 0;
			if(word != 0)
				match = false;
		}
		else if(index < 3 && tolower(string[x]) == cpp[index])
		{
			if(word < 0)
				word = 1;
			if(word != 1)
				match = false;
		}
		else if(index < 3 && tolower(string[x]) == nba[index])
		{
			if(word < 0)
				word = 2;
			if(word != 2)
				match = false;
		}
		else if(index < 4 && tolower(string[x]) == yolo[index])
		{
			if(word < 0)
				word = 3;
			if(word != 3)
				match = false;
		}
		else
			match = 0;
	}

	if(word == 0 && index < 11)
	{
		match = false;
	}
	else if(word == 1 && index < 3)
	{
		match = false;
	}
	else if(word == 2 && index < 3)
	{
		match = false;
	}
	else if(word == 3 && index < 4)
	{
		match = false;
	}

	if(match)
	{
		for(x = 0; string[x] != '\0'; x++)
			putchar(string[x]);
		putchar('O');
	}

	return 0;
}