//Exercício 10 - Campeonato
#include <iostream>
using namespace std;

int  main(){
//A entrada contém 6 inteiros , então vou ter que criar 6 variaveis do tipo inteiro
int cv, ce, cs, fv , fe, fs; //Cada vairavel esta separada por virgula
//Descrição das variavies:
//cv: quantidade de vitoria do Cormengo
//ce: quantidade de empates do Cormengo
//cs: saldo de gols do Cormengo
//fv: quantidade de vitoria do Flaminthians
//fe: quantidade de empates do Flaminthians
//fs: saldo de gols do Flaminthians
//Vou criar mais duas variaveis para guardar os pontos do Cormengo e do Flaminthians, também do tipo int.
int pontosCormengo , pontosFlaminthians ; // Observe que cada variavel criada esta separadas por virgula
//Agora o programa lerá a entrada do teclado com o cin . Como a entrada vai ser toda em uma linha usarei um unico cin
cin >> cv >> ce >> cs >> fv >> fe >> fs; //Os tres primeiros inteiros são dados do Cormengo e os ultimos tres inteiros dados do Flaminthians
//Agora o programa irá calcular os pontos do  Cormengo e  guardar o resultado na variavel  pontosCormengo , usando o comando de atribuição =
pontosCormengo =  3*cv+ce; // Cada vitoria vale 3 pontos e o empate 1 ponto
pontosFlaminthians = 3*fv+fe;
//Agora o programa irá usar o if para comparar os pontos , mas existe uma regra que diz se houver empate nos pontos ganha quem tiver o maior o saldo de gols . Pode ocorrer empate se empatarem em tudo , pontos e saldo de gols
if(pontosCormengo > pontosFlaminthians){
        cout <<  "C" ; //Os pontos do Cormengo é maior
    }else if(pontosCormengo < pontosFlaminthians){
        cout <<  "F" ; //Os pontos do Flaminthians é maior
    }else{ // Este else ou senão só será executado se os dois if acima forem falsos, isto quer dizer que os pontos estão iguais para os dois times. Vou chamar este else de else dos pontos iguais
    //Aqui dentro deste else , eu posso colocar outro [if  else-if  else] , este novo if ficará dentro do bloco {} do else
        if(cs>fs){
            cout << "C" ; //O Cormengo tem igual quantidade de pontos , mas um saldo maior
            }else if(cs<fs){
            cout <<  "F" ; //O Flaminthians tem igual quantidade de pontos , mas um saldo maior
                }else{//senão dos saldos de gols iguais. Este else ou senão só será executado se os dois if acima forem falsos, isto quer dizer que os saldos de gols são iguais.
                    cout  << "="; // Empate total, então a saida será o =
                    }//Fim do senão dos saldos de gols iguais

        }//Fim do else qdos pontos iguais(Observe que o bloco do else tem um if else-if completo)


return 0;
}
