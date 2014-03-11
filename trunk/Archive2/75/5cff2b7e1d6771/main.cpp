#include <stdio.h>
#include <errno.h>
#include <string.h>

void imprimir_asteriscos(int num_ast)
{
    printf("\n");
    for(int i=0;i<num_ast;i++)
        {
        printf("*");
        }
    printf("\n");
}
 
int main(void)
{
    int cont=0;
    int ini=0;
    int lim=100;
    int long_linea=25;
    int aum=1;
    
    //Si la longitud de la línea
    if(long_linea>(lim-ini))
        {
        long_linea=lim-ini;    
        }

    imprimir_asteriscos((long_linea*3)+1);
    
    printf("-");
    
    for(int i=ini;i<lim;i+=aum)
        {
        cont++;
        
        if(i<10)
            {
            printf("0");
            }
        
        printf("%d",i); 
        
        printf("-");
        
        if(cont>=long_linea)
            {
            if(i!=lim-1)
                {
                printf("\n-");
                }
            cont=0;
            }
        
        }
            
    imprimir_asteriscos((long_linea*3)+1);
     
    return 0;
}