#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*Faça um algoritmo de portaria de uma roda gigante que verifica se a pessoa tem mais de 1,5 mts 
    de altura e mais de 14 anos*/
	
	int idade;
	float altura;
    printf("Roda Gigante \n\n");
    printf("Digite sua Altura:\n");
    scanf("%f", &altura);
    printf("\n");
	printf("Digite sua Idade:\n");
    scanf("%i", &idade);
	
	if((altura>=1.5)&&(idade>=14)){
		printf("Seja bem vindo! Boa Diversão!");
		}
	
	else{
		printf("Acesso Bloqueado!\n");
	if(altura<1.5){
		printf("Você precisa ter pelo menos 1.5 mts de altura para brincar na Roda Gigante!\n");
	}
	if(idade<14){
		printf("Você precisa ter pelo menos 14 anos de idade para brincar na Roda Gigante!\n");
	}
		
	}
    return 0;
}



