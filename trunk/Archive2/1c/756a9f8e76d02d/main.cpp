#include <stdio.h>
main() 
{
    float n1, n2, n3, p1, p2, p3;
    scanf{%f, %f, %f, &n1, &n2, &n3};
    scanf{%f, %f, %f, &p1, &p2, &p3}; 
    m=(n1*p1 + n2*p2 + n3*p3)/(p1 + p2 + p3);
    printf("m = %.1f/n, m");
    if(m>=7){
        printf("Aprovado");
    }else{
        if(m<=4){
            printf("Reprovado");
        }else{
            printf("Prova Final, se lenhou");
        }
    }
}         