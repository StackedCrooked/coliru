//alphabet.cpp

#include <iostream>

using namespace std;

int main ()
{
    
	char A[27];				//Array vom Typ char
	A[26] = '\0';			// Letztes Element ist \0 da C-string
	
		for (int i=0;i<26;++i)    //Inhalt des Arrays - Große Buchstaben
		{
			A[i]=65+i;

			cout << A[i];   //Array wird direkt ausgegeben
		}

    cout << " ";

	char B[27]; 			//Zweites Array vom Typ char
	B[26] = '\0';			//Wie oben, C-string
	
		for (int i=0; i<26;++i)  //Inhalt des Arrays - Kleine Buchstaben
		{
			B[i]=97+i;

			cout << B[i]; //Array wird auch direkt ausgegeben
		}
cout << " " ;
//Jetzt werden beide Arrays modifiziert

for (int i=0; i<26;++i)
{	
 	if(i%2==0)        //jeder zweite Buchstabe wird mit dem kleinen äquivalten Buchstaben ersetzt
 	{				  //Also alle mit geraden Index
 		A[i]=97+i;
 	} else
 		A[i]=65+i;  //Ansonsten gibt der Array so wie oben aus

cout << A[i]; //Ausgabe des neuen modifizierten Arrays
}

cout << " ";

for (int i=0; i<26;++i)
{
 	if(i%2!=0)        //Jeder zweite Buchstabe wird ersetzt, jedoch um einen Index verschoben
 	{                 // Also alle mit einem ungeraden Index mit dem großen Buchstaben
 		B[i]=65+i;
 	} else
 		B[i]=97+i;   //Ansonsten so wie der normale Array deklariert wurde

cout << B[i];  //Ausgabe des neuen modifizierten Arrays
 	}

 cout << " ";

for (int i=0; i<26; ++i)
{

 	if (A[i]!=B[i])    //Falls die Buchstabe nicht gleich sind, gibt die Schleifen aus an welcher Stelle und unterbricht.
 		{
 			cout << "test failed at " << i;
 			return 0;
 		} else if (i==25)
 		{
			cout << "test passed"; 
		}  //Solange sie sich nicht unterscheiden wird die for schleifen bis zum Ende ausgeführt

 	}

}

