// ConsoleApplication1.cpp : definisce il punto di ingresso dell'applicazione console.
// 12.11.2014 Enrico Allais  3AT   
//if annidati , programma che dice se il voto e in suff suff buono oppure ottimo utilizzanod gli if per verificare il voto finale.
#include <stdafx.h>
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
 
		int N, somma = 0; 

		cin >> N; 
	
		for(int i=1;i<=20;i++)
			{ 
			
				int nume; 
				cin >> nume; 
				somma = somma * nume;

			} 
		cout << "SOMMA = " << somma << endl; 
		system("pause");
		return 0