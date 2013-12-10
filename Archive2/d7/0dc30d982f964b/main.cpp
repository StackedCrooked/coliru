#include <iostream>

using namespace std;

//inserisci elementi
void Insert(const char* M[][10], const int rows, const int cols)
{
	for (auto i=0; i<rows; i++)
	{
		for (auto j=0; j<cols; j++)
		{      
			M[i][j]= "A";    
		}
	}
}

void Stamp(const char* M[][10], const int rows, const int cols)
{
    //stampa della matrice
	for (auto i=0; i<rows; i++)
	{       
		for (auto j=0; j<cols; j++)
		{
			cout<<M[i][j]<<"\t";
		}
		cout<<"\n";
	}
}
	
int main (void)
{
	const char* M[10][10];
	Insert(M,10,10);
	Stamp(M,10,10);
	return 0;
}