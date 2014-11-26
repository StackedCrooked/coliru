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
		}


	char B[27]; 			//Zweites Array vom Typ char
	B[26] = '\0';			//Wie oben, C-string
	
		for (int i=0; i<26;++i)  //Inhalt des Arrays - Kleine Buchstaben
		{
			B[i]=97+i;
		}

	for(int i=0;i<27;++i)  //Ausgabe des ersten Arrays
	{ 
		cout << A[i];
	}
cout << " ";

	for(int i=0;i<27;++i)  //Ausgabe des zweiten Arrays
	{
		cout << B[i];
	}
cout << " ";

for(int i=0; i<27;++i)
{

 	for(int a=0;a<27;++a)
 	{
 		if(a%2==0)
 		{
 			cout << A[a+32];
 		} else
 			cout << A[a];	
 	}
cout << " ";

 	for (int a =0; a<27;++a)
 	{
 		if(a%2!=0)
 		{
 			cout << B[a-32];
 		} else
 			cout << B[a];
 	}

 cout << " ";

 	if (A[i]!=B[i])
 		{
 			cout << "test failed at " << i;
 			return 0;
 		} else

 		cout << "test passed";
 		return 0;
 	}

}
 
