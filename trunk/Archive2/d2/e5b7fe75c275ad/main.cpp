#include <iostream>
using namespace std;

int tab1[5];
double tab2[5];
long tab3[5];
int i;
long suma=0;

int main()
{
for (i=0; i<=6; i++)
   {cout << "Wprowadź " << i+1 << "element :";
    cin >> tab1[i];}
	
for (i=0; i<=5; i++)
	suma=suma+tab1[i];

cout << "Suma = " << suma;
}