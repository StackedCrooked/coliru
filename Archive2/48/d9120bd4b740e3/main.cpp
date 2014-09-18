#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 int main(){
     float heures, code, age, acc, prat;
     printf("quel age avez vous?\n");
	 scanf("%f",&age);
	 printf("avez vous fait de la conduite accompagnée?\n");
	 scanf("%f",&acc);
	 printf("avez vous le code?\n");
	 scanf("%f",&code);
	 printf("avez vous au moins une année de pratique?\n");
	 scanf("%f",&prat);
	 printf("combien d'heures de lecons avez vous pris?\n");
	 scanf("%f",&heures);
	 if((age>=18 && code==1) && ((acc==0 && heures>=20)||(acc==1 && prat==1 && heures>=21))){
		printf("passage autorisé");
	 }else{
		printf("passage refusé");
	 
	 }}
 