#include <iostream>
using namespace std;

int main()
{
   char palavra[64] = {}, jafoi[64] = {}, letra = '#';
    int erros = 0;
	char letrasErradas[6];
	cout << "Escolha uma palavra"<< endl;
	cin >> palavra;


	int contadorAcertos = 0;
	while(erros < 6 && letra != '0' && contadorAcertos != 64)
	{
		contadorAcertos = 0;

		cout << endl;
		cout << "Informe uma letra" << endl;
		cin >> letra;
		cout << endl;
		system("cls");
		bool  tipo = false;

		bool letra_repetida = false;
		for (int auxiliar=0; auxiliar< 64; auxiliar++)
		{
			if (jafoi[auxiliar]==letra)
			{
				letra_repetida= true;
				cout << "voce ja digitou a seguinte letra" << letra;
			}
		}
		for (int auxiliar=0; auxiliar < 6; auxiliar ++)
		{

			if (letrasErradas[auxiliar]==letra)
			{
				letra_repetida= true;
				cout << "voce ja digitou a seguinte letra: " << letra;
			}
		}
		if(letra_repetida== false)
		{

			for (int contador = 0; contador < 64; contador++)
			{
				if (letra == palavra[contador])
				{
					tipo = true;
					jafoi[contador] = letra;

				}
				cout << jafoi[contador];
			}

			if (tipo == false)
			{
				letrasErradas[erros]=letra;
				erros++;
			}
		}
		cout<<endl;

		switch(erros)
		{

		case 6:	cout<<" o "<<endl;
			cout<<"/|\\"<<endl;
			cout<<"/\\ "<<endl;
			break;
		case 5:	cout<<" o "<<endl;
			cout<<"/|\\"<<endl;
			cout<<"/"<<endl;
			break;

		case 4:	cout<<" o "<<endl;
			cout<<"/|\\"<<endl;
			break;

		case 3:	cout<<" o "<<endl;
			cout<<"/|"<<endl;
			break;

		case 2:	cout<<" o"<<endl;
			cout<<"/"<<endl;
			break;

		case 1:	cout<<" o "<<endl;
			break;


			
		}
		for(int i = 0; i < 64; i++)
		{
			if(palavra[i] == jafoi[i])
			{
				contadorAcertos++;
			}
		}

	}

	if(contadorAcertos == 64)
	{
		cout << "Parabens! =D" << endl;
	}
	else if(letra == '0')
	{
		cout << "Voce abandonou o jogo!" << endl;
	}
	else
	{
		cout << "Voce perdeu!" << endl;
	}

	system("pause");

}
