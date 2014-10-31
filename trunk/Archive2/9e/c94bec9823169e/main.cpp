#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std;

const int MAX_ALUNNI = 35;
const int MAX_MATERIE = 15;

int pagella[MAX_ALUNNI][MAX_MATERIE];


string alunni[MAX_ALUNNI];
string materie[MAX_MATERIE];

void inserisciAlunniMaterieVoti(int pagella[MAX_ALUNNI][MAX_MATERIE], int n_alunni, int n_materie)
{
	
	for(int a=0;a<n_alunni;a++)
	{
		cout << "Alunno: " << endl;
		cin >> alunni[a];


		for(int m=0;m<n_materie;m++)
		{
			cout << "Materia: " << endl;
			cin >> materie[m];
		
				
			cout << "voto: " << endl;
			cin >> pagella[a][m];
		}
	}
}


	

int main(int argc, char *argv[])
{


	inserisciAlunniMaterieVoti(pagella, 10, 15);






	fflush(stdin);
	getchar();
	
	return 0;
}