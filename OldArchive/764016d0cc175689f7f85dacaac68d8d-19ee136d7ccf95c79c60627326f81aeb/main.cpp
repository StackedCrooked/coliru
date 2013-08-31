#include <stdio.h>


void Afficher(int Tab[5][5], int size){ //Affiche la grille

        for (int i=0; i<=size-1; i++){
                for (int j=0; j<=size-1;j++){
                        if (Tab[i][j]==1) printf("X ");
                        else printf("%d ",Tab[i][j]);
                }
        printf("\n");
        }
}

void Check(int Tab[5][5], int Tabn[5][5], int size){
        for (int i=0; i<=size-1; i++){
                for (int j=0; j<=size-1;j++){
                        int sum = 0; //on vérifie l'état des cellules alentoures sans déborder du tableau
                        if (i+1<=4) sum = sum + Tab[i+1][j]; //cellule ... à droite
                        if (i-1>=0) sum = sum + Tab[i-1][j]; //à gauche
                        if (j+1<=4) sum = sum + Tab[i][j+1]; //en bas
                        if (j-1>=0) sum = sum + Tab[i][j-1]; // en haut
                        if (i-1>=0 && j-1>=0) sum = sum + Tab[i-1][j-1]; //en haut à gauche
                        if (i-1>=0 && j+1<=4) sum = sum + Tab[i-1][j+1]; //en bas à gauche
                        if (i+1<=4 && j-1>=0) sum = sum + Tab[i+1][j-1]; //en haut à droite
                        if (i+1<=4 && j+1<=4) sum = sum + Tab[i+1][j+1]; //en bas à droite
                        if (Tab[i][j] == 1 && sum<2) Tabn[i][j] = 0; //si une cellule vivante ne remplie pas les conditions, elle meurt à t+1
                        else if (Tab[i][j] == 0 && sum>=3) Tabn[i][j] = 1; //si une cellule morte remplie conditions, elle vie à t+1
            }
        }
}


int main(int argc, char **argv){

        int Tab[5][5], Tabn[5][5];


        for (int i=0; i<=4; i++){
                for (int j=0; j<=4;j++){
                        Tab[i][j]=0;
                }
        } //rempli tableau au temps t avec des cellules mortes
        Tab[2][1]=1;Tab[2][2]=1;Tab[2][3]=1; //On ajoute des cellules vivantes

        Afficher(Tab,5);//affiche la grille

        for (int i=0; i<=4; i++){
                for (int j=0; j<=4;j++){
                        Tabn[i][j]=Tab[i][j];
                }
        }//recopie la grille dans nouveau tableau au temps t+1

    Check(Tab,Tabn,5);


        printf("\n");
        Afficher(Tabn,5); //affiche la nouvelle grille au temps t+1
}

