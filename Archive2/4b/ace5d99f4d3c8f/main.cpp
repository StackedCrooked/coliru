char* MajToMin(const char*);
char* SumCharsAndDigits(const char*);

/*------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    return 0;
}

/*------------------------------------------------------------------------------------------*/

char* SumCharsAndDigits(const char* str){
	double somme;
	char value;
	int i = 0;
	int compteur = 0;

	while (str[compteur] != '/0'){// calcul de la taille de str
		compteur ++;
	}

	//const char* tab = malloc(str);
	const int taille = compteur; 
	char* tab[taille];
	//char* tab  = str;
	//char* tab[] = str;

	while (tab[i] != '/0'){ // on parcourt la chaine de caractère
			i ++; // incrémentation
			if (tab[i]<= '0' || tab[i] >= '9'){
				tab[i] = MajToMin(&str[i]); // on passe les majuscules en minuscules
				if (tab[i]<='a' || tab[i] >= 'z'){ // si le caractère n'est pas entre a et z
					value = '0'; // on lui assigne 0
				}
				else { //s'il est entre a et z
					value = tab[i] - 'a';
				}
			
				tab[i] = value; // on change la valeur des caractères : éléments de ascii vers valeur alphabet
			}
	}
	
	while(somme > 9){
		//somme = strtol(somme, NULL, 10);
	}
}

/*------------------------------------------------------------------------------------------*/
char* MajToMin(const char* c) { 
	char value;
    if(*c>='A' && *c<='Z'){
		value = *c+('a'-'A');
        return &value; 
	}
    else 
		value = *c;
        return &value; 
}
