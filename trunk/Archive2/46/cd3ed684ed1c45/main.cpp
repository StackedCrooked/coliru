#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    return 0;
}

/*------------------------------------------------------------------------------------------*/

char* SumCharsAndDigits(const char* str){
	double somme;
	char value;
	int i = 0;
	char sol = *str;

	while (str[i] != '/0'){ // on parcourt la chaine de caractère
			i ++; // incrémentation
			sol[i] = MajToMin(&str[i]); // on passe les majuscules en minuscules
			value = str[i] - 'a';
			str[i] = value; // on change la valeur des caractères : éléments de ascii vers valeur alphabet
		}
	somme = strtol(str, NULL, 10);
	
	while(somme > 9){
		somme = strtol(somme, NULL, 10);
	}
}

/*------------------------------------------------------------------------------------------*/
const char* MajToMin(const char* c) { 
	char value;
    if(*c>='A' && *c<='Z'){
		value = *c+('a'-'A');
        return &value; 
	}
    else 
        return c; 
}
