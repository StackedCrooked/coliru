#include <stdio.h>
#include <string.h>
#include <math.h>
struct dados{
    int rendaMensal;
    int Ndependentes;
    char CPF[20];
    int RendaFinal;
}pessoas;

int main(){
float SalarioMinimo = 0.0;
int contribuintes = 0;
int QuantidadeSalarios = 0;
struct dados pessoas[500];



printf("Numero de Contribuintes: \n");
scanf("%d", &contribuintes);

printf("Salario Minimo atual: ");
scanf("%f", &SalarioMinimo);


int i;
for(i=0;i<contribuintes;i++){
    getchar();
    printf("CPF: ");
    gets(pessoas[i].CPF);

    printf("Renda Mensal: ");
    scanf("%d", &pessoas[i].rendaMensal);

    printf("Numero de dependentes: ");
    scanf("%d", &pessoas[i].Ndependentes);

    //printf("%s", pessoas[i].CPF);
   QuantidadeSalarios = round((pessoas[i].rendaMensal)/SalarioMinimo);


    if(QuantidadeSalarios < 2){
         pessoas[i].RendaFinal = pessoas[i].rendaMensal;
    }else if((QuantidadeSalarios > 2) && (QuantidadeSalarios < 3)){
        pessoas[i].RendaFinal = ((0.05*pessoas[i].rendaMensal))*(1-(pessoas[i].Ndependentes*0.05));
    }else if((QuantidadeSalarios > 3) && (QuantidadeSalarios < 5)){
        pessoas[i].RendaFinal = ((0.10*pessoas[i].rendaMensal))*(1-(pessoas[i].Ndependentes*0.05));
    }else if((QuantidadeSalarios > 5) && (QuantidadeSalarios < 7)){
        pessoas[i].RendaFinal = ((0.15*pessoas[i].rendaMensal))*(1-(pessoas[i].Ndependentes*0.05));
    }else if(QuantidadeSalarios > 7){
        pessoas[i].RendaFinal = ((0.20*pessoas[i].rendaMensal))*(1-(pessoas[i].Ndependentes*0.05));
    }


printf("%d ", pessoas[i].RendaFinal);
}