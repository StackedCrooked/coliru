#include <iostream>

using namespace std;

int main()
    {
    //instrução para criar três variáveis
    double p1,p2,p3;
    //instrução para criar a variável média
    double media;
    //instrução para ler três números em uma linha
    //guardando nas variáveis p1,p2 e p3
    cin >> p1 >> p2 >> p3;
    //instrução para calcular a média,usando o comando de atribuição =
    media=(p1+p2+p3)/3;
    cout.precision(2);
    cout << media << endl;
    //comando condicional
    if (media>=5.0){
        cout << "Aprovado";
        }else{
        cout << "Reprovado";
        }
    return 0;
    }