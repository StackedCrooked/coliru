
#include <stdio.h>


int main()
{

    FILE *fp = fopen ("C:\\users\\admin\\Dokumenty\\tabulka.txt", "r");

	if (NULL == fp)
		printf("No found\n");
	
	fclose(fp);
char str[1024]=""	
while (!feof(fp))
{
fgetc(str, 1024, fp);
printf ("%s",str);
}
	getchar();

	return (0);
}