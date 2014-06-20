#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<iostream>

using namespace std;

int RandNumber(int MinNumber, int MaxNumber){
    srand(time(NULL)*111);
    int randomNumber = MinNumber + (rand() % (MaxNumber+1-MinNumber));
    return randomNumber;
    }

int main()
{
    int erros = 6;
    while(erros>0){
    char animais[][100] = {  "Abelha", "Albatroz", "Alce", "Anta", "Aranha",
                                "Araponga", "Asno", "Avestruz", "Baleia", "Barata",
                                "Beija-flor", "Bicho-preguiça", "Borboleta", "Bufalo", "Cabra",
                                "Cagado", "Calango", "Camaleao", "Camelo", "Cachorro",
                                "Capivara", "Carneiro", "Carrapato", "Cascavel", "Castor",
                                "Cavalo", "Chupim", "Cigarra", "Cisne", "Coala",
                                "Cobaia", "Cobra-cega", "Coelho", "Condor", "Corvina",
                                "Corvo", "Crocodilo", "Dourado", "Dragao-de-comodo", "Elefante",
                                "Ema", "Esquilo", "Foca", "gafanhoto", "galinha",
                                "gamba", "ganso", "garoupa", "gato", "gaviao",
                                "girafa", "golfinho", "gorila", "gralha", "lobo-guara",
                                "Hamster", "Hipopotamo", "Homen", "jaburu", "jabuti",
                                "jacare", "jacutinga", "jaguatirica", "jararaca", "joao-de-barro",
                                "joboia", "lagarto", "lagartixa", "lambari", "leao",
                                "Lebre", "leopardo", "lhama", "libellula", "lince",
                                "lobo", "lombriga", "lontra", "lula", "marreco",
                                "mico-leao-dourado", "mosquito-da-dengue", "orangotango", "ostra", "paca"
                                "pacu", "panda", "papagaio", "pato", "pavao",
                                "peixe-espada", "peru", "pica-pau", "pinguim", "pintado",
                                "piolho", "piranha", "pirarocu", "polvo", "pombo",
                                "porco", "pulga", "pulgao", "puma", "quero-quero",
                                "Raposa", "rato", "rinoceronte", "salmao", "sapo",
                                "saracura", "sardinha", "tamandua", "tatu", "tico-tico",
                                "tigre", "touro", "vaca", "traira", "tucano",
                                "tucunare", "uirapuru", "urso", "urubu", "urutu",
                                "veado", "vespa", "xexeu", "zebra", "zorrilho"
                            };
            //char animaisx[130][100];

            int numeroo = RandNumber(1, 130);
            char dica[10] = {"ANIMAL"};
            int tamanhopalavra = strlen(animais[numeroo]);

            printf("Dica: ANIMAL           Erros: %d\n", erros);
            printf("-----;\n|    |\n|\n|\n|\n|\n\n");
            //char letra;
            /*for(int i=1; i<=tamanhopalavra; i++){
                if(strncmp(animais[numeroo], '-') == 0)
                {
                    printf("-");
                    setbuf(stdin, NULL);
                }
                else
                {
                    printf("_ ");
                    setbuf(stdin, NULL);
                }
            }
            */
            for(int i=1; i<=tamanhopalavra; i++){
                printf("_ ");
            }

            printf("\nDica: %s      Numero: %d     Palavra: %s", dica, numeroo, animais[numeroo]);
            cin.get();
            //system("cls");
            erros--;
            } //final do while(erros>5)
            printf("Voce e um bosta, e perdeu feio!");
            cin.get();
    return 0;
}
