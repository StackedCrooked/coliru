#include  <iostream>
#include <string>
using namespace std;
int main()
    {
    //instrução para criar três variáveis
    double p1,p2,p3;
    //instrução para criar a variável media
    double media;
    //instrução para ler três números em uma linha
    //guardando nas variáveis p1,p2,p3
    cin >> p1 >> p2 >> p3;
    //instrução para caulcular a média,usando o comando
    //de atribuição =
    media=(p1+p2+p3)/3;
    //primeira linha já aprendemos
    cout <<media <<endl;
    cout.precision(2);
    if(media>=5.0){
       cout << "aprovado";
    }else{
       cout << "reprovado";
       }






    return 0;
    }
