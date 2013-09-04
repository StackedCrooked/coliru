#include<stdio.h>

int main()
{
    printf("How old are you?\n");
	int age=0;
    char input[1000];
    fgets(input, 1000, stdin);
    printf("The input was: '%s'\n", input);
    
    if(age > 18)
        printf("You can drive a car.");
    else
        printf("You will have to walk.");
        
	return 0;
}