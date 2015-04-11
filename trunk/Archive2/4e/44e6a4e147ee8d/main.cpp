//Aula de If onze de abril-sabado
#include <iostream>
using namespace std;
int main()
    {
    //Instrução para criar três variáveis
    double p1,p2,p3;
    //Instrução para criar a variável media
    double media;
    //Instrução para ler três números em uma linha
    //guardando nas variáveis p1,p2,p3
    cin>> p1>>p2>>p3;
    //Instrução para calcular a média, usando o comando
    //de atribuição '='
    media=(p1+p2+p3)/3;
    //primeira linha já aprendemos
    cout.precision (2);
    cout<< media << endl;
    
    //na segunda linha precisamos decidir por "aprovado"
    //ou "reprovado"
    //IF=se ELSE=senão
    //operador de comparaçao >=
    //IF comandocondicional
    // == igual a
    // != diferente de
    if(media>=5.0)
    {cout<< "aprovado";}

    else{cout<< "reprovado";}



return 0;
    }
