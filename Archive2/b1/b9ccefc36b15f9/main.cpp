#include <stdio.h> 
#include <conio.h>
main()
{//inicio do programa
//Declaracao das variaveis do programa
char R1, R2, R3, R4, continuar;
//Entrada de dados do programa
printf(“ Voce estudou para a prova? Responda S para sim e N para nao.”);
R1 = getch();
printf(“ voce vai passar em introduao a computação? Responda S para sim e N para nao.”);
R2 = getch();
printf(“ voce entendeu a materia? Responda S para sim e N para nao.”);
R3 = getch();
printf(“ voce acha que consegue ajudar seus amigos? Responda S para sim e N para nao.”);
R4 = getch();
if (R1 = = 'S')
 printf( “ voce esta indo muito bem.”);
else
 if((R2 = = 'S')
 printf( “ voce e uma boa aluna.”);
 else
 if(R3 = = 'S' && R4 = = 'S')
 printf( “ parabens.”);
if((R1 = = 'S' || R2 = = 'S') && (R3 = = 'S' && R4 = = 'S'))
 printf( “continue assim.”);
}
