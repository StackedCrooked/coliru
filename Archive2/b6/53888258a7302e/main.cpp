// Type your code here, or load an example.
/*
**    L6 internal project
**
**  read a text file 
**  convert to ASCII
**  send to arduino board
*/ 

#include <stdio.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
    FILE* fichier_src = NULL ;
	FILE* fichier_2 = NULL ;
	char phrase[33] ="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ; 
	char lettre;
	int i = 0;
	
	
    //fichier = fopen("/media/mmc/rep4all/text4lcd.txt" , "r");
	fichier_src = fopen("../../management.txt" , "r+");
	
	if(fichier_src !=NULL)
	{
	    printf("\n \n");
		printf("fichier ouvert\n");
		printf("phrase initiale : %s \n",phrase);
		//fscanf(fichier, "%s" , &phrase);
		
		while(lettre!='\n')
		{
		    lettre=fgetc(fichier_2);
		    phrase[i]=lettre;
		    //printf("lettre : %c \n",phrase[i]);
			i++;
		}
		fichier_src = fopen("management_2.txt" , "w+");
		fwrite(phrase , sizeof(i), sizeof(phrase), fichier_2);
		fclose(fichier_2);
		
		fclose(fichier_src); // On ferme le fichier qui a été ouvert
	}    
	else{
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier management.txt");
    }
	
	return 0;	
}
