#include <iostream>
using namespace std;
int main ()
{
    int cont;
	float valor, acumulador;
	acumulador = 0;
	for(cont=1; cont<=10; cont++)
	{
		cout<<"\nNumero: "<<cont;
		cin>>valor;
		acumulador = acumulador + valor;
	}
	cout<<"\nSoma dos Valores: "<<acumulador;
system("pause");
}