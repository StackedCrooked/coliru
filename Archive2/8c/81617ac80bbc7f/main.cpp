#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std; 

int main()
{
    int i=0;
	int j=0;
	int k=0;
	int l=0;
	string tmpWORD = "";
	
	ofstream fichierResultats("resultat.csv", ios::out | ios::trunc);
	
	for(i=0 ; i<=255; i++)
	{
		for(j=0 ; j<=255; j++)
		{
			for(k=0 ; k<=255; k++)
			{
				for(l=0 ; l<=255; l++)
				{
					tmpWORD = "";
					fichierResultats << tmpWORD << endl;
					
				} // FIN l
			} // FIN k		
		} // FIN j	
	} // FIN i
	return 0;
}