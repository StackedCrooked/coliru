#include <stdio.h>

typedef struct {
    char nome[50];
	float n1, n2;
} aluno;

void preenche_aluno(aluno *a){
	printf("entre com o nome:");
	scanf("%s", a->nome);
	printf("entre com a nota1:");
	//scanf("%f", &(*a).n1);
	scanf("%f", &a->n1);
	printf("entre com o nota2:");
	scanf("%f", &a->n2);
}

void imprime_aluno(aluno *a){
	printf("Nome: %s\n", a->nome);
	printf("Media: %f\n\n", ((a->n1)+(a->n2))/2);
}

int main(){
	aluno turma[3];
	int i;
	for(i=0;i<3;i++)
		preenche_aluno(&turma[i]);
	for(i=0;i<3;i++)
		imprime_aluno(&turma[i]);
	return 0;
}
