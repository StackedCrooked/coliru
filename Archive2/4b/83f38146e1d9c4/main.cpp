#include <iostream>
using namespace std;

int  main(){
double tempo1,tempo2;//tempos restante para terminar a corrida da charrete 1 e 2
int n1,d1,v1,n2,d2,v2;//Entrada do problema
//n1 : numero da charrete da primeira linha
//d1 : distancia, da charrete da primeira linha, até a linha de chegada
//v1 : velocidade, da charrete da primeira linha, até a linha de chegada.
//n2 : numero da charrete da segunda linha
//d2 : distancia, da charrete da segunda linha, até a linha de chegada
//v2 : velocidade, da charrete da segunda linha, até a linha de chegada.
cin >> n1 >> d1 >> v1; //lendo os dados da primeira charrete
cin >> n2 >> d2 >> v2; //lendo os dados da segunda charrete
//A velocidade esta em km/h e é preciso transformar em m/s. Faço isso dividindo por 3.6
//Usando a formula v=d/t posso reformular para t=d/v (lembre-se v tem que ser divido por 3.6)
tempo1=d1/(v1/3.6); //d1 em metros e a velocidade v1 transformada em m/s terei assim o tempo tempo1 em segundos
tempo2=d2/(v2/3.6); //d2 em metros e a velocidade v1 transformada em m/s terei assim o tempo tempo2 em segundos
//if para verifica o menor tempo . Foi garantido que não haveria empates.
if(tempo1<tempo2){
    cout << "\n" << n1; // imprime em uma nova linha o numero da charrete da linha 1
}else{
    cout << "\n" << n2; // senão imprime em uma nova linha o numero da charrete da linha 2
}

return 0;
}