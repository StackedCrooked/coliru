#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
    int qtdade, count, tipo, cm, total1, total2, total;
	total1 = 1;
	total2 = 1;
	cout<<"\n Quantos anúncios deseja fazer? \n\n";
	cin>>qtdade;
	for(count=1;count<=qtdade;count++)
	{
		cout<<"\n Escolha o tipo de anúncio: (1-Venda (10 Reais o cm), 2 Aluguel (8 Reais o cm):\n\n";
		cin>> tipo;
		cout<<"\n Digite a quantidade de cm do anúncio " <<count<< ": \n\n";
		cin>> cm;
		if(tipo == 1)
		{
			total1 = total1 + (cm * 10);
			cout<<"\n Tipo do anúncio :" <<tipo<< "-Venda \n\n";
		}
		else
		{
			total2 = total2 + (cm * 8);
			cout<<"\n Tipo do anúncio :" <<tipo<< "-Aluguel \n\n";
		}
		cout<<"\n Quantidade de Cm :" <<cm<< "\n\n";
	}
	total = total1 + total2;
	cout<<"\n Valor a Pagar:" <<total<< "\n\n";
	system( "pause" );
} 