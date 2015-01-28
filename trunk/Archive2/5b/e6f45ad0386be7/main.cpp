#include <iostream>
#include <string.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	char stringa[100], c;
	int i, j, contavocali;
	
	cout << "Inserisci un testo: ";
	//input da tastiera
	i=0;
	while (i<=99){
		stringa[i] = getchar();
		//stringa[i]=c;
		if (stringa[i]=='\n') {
			stringa[i]='\0';
			break;}
		i++;
	}	
	printf ("%s", stringa);
	
	//conteggio vocali
	i=0;
	contavocali=0;
	while(stringa[i] != '\0'){
		if (!(stringa[i]=='A' || stringa[i]=='a' 
			|| stringa[i]=='E' || stringa[i]=='e' 
			|| stringa[i]=='I' || stringa[i]=='i' 
			|| stringa[i]=='O' || stringa[i]=='o' 
			|| stringa[i]=='U' || stringa[i]=='u')&&
			((stringa[i]>=97 && stringa[i]<=122 )||(stringa[i]>=65 && stringa[i]<=90 ))) {
				contavocali++;
			}
		i++;
	}
	cout << endl<<endl;
	cout << "Il testo contiene " << contavocali << " consonanti.";
	
	//trasformo le minuscole in maiuscole
	i=0;
	while(stringa[i] != '\0'){
		if (stringa[i]>=97 && stringa[i]<=122)
			stringa[i] = stringa[i] - 32;
	i++;
	}	
	cout << endl<<endl;	
	printf("%s", stringa);
	
	//tolgo le vocali

	cout << endl<<endl;	
	//printf("%s", stringa);	
	return 0;
}
