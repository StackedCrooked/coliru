#include <iostream>
#include <string>
using namespace std;

int main()
    {
    string nome;

    cout << " Digite seu nome: ";
    //cin >> nome;
    cout <<"\nolá " << nome <<endl;

    int num1;
    int num2;
    int soma;

    cout << "Digite um número" << endl;
    cin >> num1;
    cout << "Digite outro número" <<endl;
    cin >> num2;
    soma = num1+num2;
   // soma = 5;
    cout << "\n NUM1 = " << num1 << endl;
    cout << "NUM 2 = " << num2 << endl;
    cout << "------------------NUM1+NUM2---------------" << endl;
    cout << "Soma = " << num1+num2 << endl ;
    cout << "Soma = " << soma ;


    return 0;
    }
