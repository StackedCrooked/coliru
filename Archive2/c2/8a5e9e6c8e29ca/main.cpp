#include<stdio.h>
#include<stdlib.h>

main(){
       int  PROFISSAO;
       float HORA=50.00 , SALARIO , BONUS , TOTAL, VENDA;  
       printf("Informe cada cargo \n 1- Diretor \n-2 Gerente \n-3 Desenvolvedor \n-4 Vendedor \n ");
       scanf("%d", &PROFISSAO);
       
          if(PROFISSAO ==1){
          printf("10.000");
          }else if(PROFISSAO ==2){
          printf("6.000 + bonus");
          }else if(PROFISSAO ==3){
          printf("informe a quantidade de horas");
          scanf("%d",& HORA);
          TOTAL=(HORA*TOTAL);
          printf("Desenvolverdor recebe %f",TOTAL);
          }else if(PROFISSAO == 4){
          printf("Digite o valor de vendas");
          scanf("%f",&VENDA);
          printf("Valor venda + comissao e: %f\n",1000+VENDA*0.1);}
          
          system("pause");
    
       
}