#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    int nota10, nota20, nota50, ValorDoSaque;
    float total;
    printf(" --- Caixa Automatico ---\n\n");
    fflush(stdout);
    getche();

   //------------------------------------------------------------------------------------------------------------ Digitar a quantidade de notas (FUNCAO)
   system("cls");
    printf(" --- Digitacao da quantidade de notas ---\n\n");
    printf(" - Notas de 10: ");
    fflush(stdout);
    do{
        scanf("%d",&nota10);
        fflush(stdin);

        if(nota10<0)
        {
            system("cls");
            printf(" --- Digitacao da quantidade de notas ---\n\n");
            printf("Valor Invalido! Digite Novamente!\n\n");
            printf(" - Notas de 10: ");
            fflush(stdout);
        }
        else
        {
            system("cls");
            printf(" --- Digitacao da quantidade de notas ---\n\n");
            printf(" - Valor salvo com sucesso!\n\n");
            printf(" Pressione ENTER para continuar!!\n\n");
            fflush(stdout);
            getche();


        }
    }while(nota10 < 0);

     system("cls");
    printf(" --- Digitacao da quantidade de notas ---\n\n");
    printf(" - Notas de 20: ");
    fflush(stdout);
    do{
        scanf("%d",&nota20);
        fflush(stdin);

        if(nota20<0)
        {
            system("cls");
            printf(" --- Digitacao da quantidade de notas ---\n\n");
            printf("Valor Invalido! Digite Novamente!\n\n");
            printf(" - Notas de 20: ");
            fflush(stdout);
        }
        else
        {
            system("cls");
            printf(" --- Digitacao da quantidade de notas ---\n\n");
            printf(" - Valor salvo com sucesso!\n\n");
            printf(" Pressione ENTER para continuar!!\n\n");
            fflush(stdout);
            getche();

        }
    }while(nota20 < 0);


 system("cls");
    printf(" --- Digitacao da quantidade de notas ---\n\n");
    printf(" - Notas de 50: ");
    fflush(stdout);
    do{
        scanf("%d",&nota50);
        fflush(stdin);

        if(nota50<0)
        {
            system("cls");
            printf(" --- Digitacao da quantidade de notas ---\n\n");
            printf("Valor Invalido! Digite Novamente!\n\n");
            printf(" - Notas de 50: ");
            fflush(stdout);
        }
        else
        {
            system("cls");
            printf(" --- Digitacao da quantidade de notas ---\n\n");
            printf(" - Valor salvo com sucesso!\n\n");
            printf(" Pressione ENTER para continuar!!\n\n");
            fflush(stdout);
            getche();

        }
    }while(nota50 < 0);




            //--------------------------------------------------------------------------------------- Mostra a quantidade de cedulas em caixa (FUNCAO)

            system("cls");
            printf(" --- Caixa Automatico ---\n\n");

            printf(" - Quantidade de cada Cedula no Caixa - \n\n");

            printf(" Cedula(as) de R$ - 10: %d\n",nota10);
            printf(" Cedula(as) de R$ - 20: %d\n",nota20);
            printf(" Cedula(as) de R$ - 50: %d\n\n",nota50);

            total = (nota10*10) + (nota20*20) + (nota50*50);

            printf(" Total Disponivel: %.02f\n\n\n\n",total);

            printf(" Pressione ENTER para para efetuar o saque!!\n\n");
            fflush(stdout);
            getche();



           // -------------------------------------------------------------------------------------- Chamado do MENU

            
             int opcao;
             
             do{
                 printf("\n\n***''''''''''''''''''''''''''''''''''''***\n");
                 printf("*******      CAIXA AUTOMATICO      *******\n");
                 printf("**''''''''''''''''''''''''''''''''''''''**\n");
                 printf("**                                      **\n");
                 printf("** 0 - SAIR                             **\n");
                 printf("** 1 - MOSTRAR VALORES DO CAIXA         **\n");
                 printf("** 2 - INFORMAR SALDO DO CLIENTE        **\n");
                 printf("** 3 - DEFINIR SALDO DO CLIENTE         **\n");
                 printf("** 4 - DEFINIR LIMITE MAXIMO PARA SAQUE **\n");
                 printf("** 5 - REALIZAR SAQUE                   **\n");
                 printf("**                                      **\n");
                 printf("***''''''''''''''''''''''''''''''''''''***\n\n");
                 
                 
                 printf("OPCAO: ");
                 scanf("%d",&opcao);
                 
                 switch(opcao)
                 {
                    case 0:
                        printf("Saindo do Menu!");
                        break;
                        
                    case 1:
                        printf("Valores do Caixa");
                        break;
                    
                    case 2:
                        printf("Saldo do Cliente");
                        break;
                        
                    case 3:
                        printf("Definir Saldo");
                        break;
                        
                    case 4:
                        printf("Definir Limite de Saque");
                        break;
                        
                    case 5: 
                        printf("Realizar Saque");
                        break;
                        
                    default:
                        printf("OPCAO INVALIDA!!! Tente Novamente!");
                        
                 }
                 
                }while(opcao != 0); 
             
             





