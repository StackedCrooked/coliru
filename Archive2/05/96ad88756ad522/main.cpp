#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arbre_t {
    
	int root ;
	struct arbre_t *Agauche ;	// cree le sous arbre de gauche
	struct arbre_t *Adroite ;	// cree le sous arbre de droite
	
	} arbre ;




	
void Ajouter(arbre **T, int c) {
	if (*T == NULL) {						//si larbre est null, elle cree la racine et initialise les deux branches
		*T=(arbre*)malloc(sizeof(arbre));
		(*T)->root =c;
		(*T)->Agauche = NULL;
		(*T)->Adroite = NULL;
	}
	else{									// place les nombres plus petits a gauche et les autres a droite
		if((*T)->root > c) 
		Ajouter(&(*T)->Agauche, c);
		
		else
		Ajouter(&(*T)->Adroite, c);
	}
	}





void Afficher(arbre **T) {
	if (*T != NULL) {
		//printf("%d\n", (*T)->root) ;
		Afficher(&(*T)->Agauche);
		printf("%d\n", (*T)->root) ;
		Afficher(&(*T)->Adroite);
	}
	
}	





int Rechercher(arbre **T, int c) {
	if(*T==NULL) {
		printf("PAS Trouvé");
		return 0;
	}
	else{
			if ((*T)->root==c) {
			printf("Trouvé: %d\n", c);
			return 0;
		}
			else {
				if (c < ((*T)->root))
				Rechercher((&(*T)->Agauche), c);
				else
				Rechercher((&(*T)->Adroite), c);
			}
	}
	return 0;
}




int Min(arbre **T) {  // le minimum se trouve tout a gauche de larbre a la fin
	arbre *tmpo;
	tmpo=*T;
	if(tmpo != NULL) {
		while(tmpo->Agauche !=NULL){
			tmpo=tmpo->Agauche;
		}
	printf("Minimum: %d\n", tmpo->root);
	return (tmpo->root);
	}
	else {
	printf("arbre vide");
	}
	return 0;
} 





int Max(arbre **T) {  // le maximum se trouve tout a droite de larbre a la fin
	arbre *tmpo;
	tmpo=*T;
	if(tmpo != NULL) {
		while(tmpo->Adroite !=NULL){
			tmpo=tmpo->Adroite;
		}
	printf("Maximum: %d\n", tmpo->root);
	return (tmpo->root);
	}
	else {
	printf("arbre vide");
	}
	return 0;
	
} 



int Taille(arbre **T) {
	if(*T==NULL){
		return 0;
	}
	else
	return (1 + Taille(&(*T)->Agauche) + Taille(&(*T)->Adroite) );
}


int max(int a, int b) {  //selectionne le maximum entre deux nombres (pour la fonction Pronfondeur)
	
	if (a>b)
	a=b;
	
	return a;
}


int Profondeur(arbre **T) {
	if(*T==NULL)
		return 0;
		
	else{
		
		return (1 + max (Taille(&(*T)->Agauche) , Taille(&(*T)->Adroite) ));
		
		}	

}





void quicksort(int tableau[100000],int a,int z){
    int pivot,j,tempo,i;

     if(a<z){
         pivot=a;
         i=a;
         j=z;
      
         while(i<j){  
             while(tableau[i]<=tableau[pivot]&&i<z) 
                 i++;
             while(tableau[j]>tableau[pivot]) 
                 j--;
             if(i<j){
                 tempo=tableau[i];
                  tableau[i]=tableau[j];
                  tableau[j]=tempo;
             }
         }

         tempo=tableau[pivot]; 
         tableau[pivot]=tableau[j];
         tableau[j]=tempo;
         quicksort(tableau,a,j-1);
         quicksort(tableau,j+1,z);

    }
}





int main ( int argc, char** argv, char** envv ) {
srand(time(NULL));	
	arbre *N;
	arbre *K;
	N = NULL;
	K = NULL;
	int i;
	int tab;
	int p = 100000;
	int* table;
	table = (int*)malloc(sizeof(int)*p);
	
	Ajouter(&K, 7);
	Ajouter(&K, 14);
	Ajouter(&K, 9);
	Ajouter(&K, 11);
	Ajouter(&K, 10);
	Ajouter(&K, 4);
	Ajouter(&K, 6);
	Ajouter(&K, 5);
	Ajouter(&K, 15);
	Afficher(&K);
	Rechercher(&K, 14);
	Min(&K);
	Max(&K);
	printf("Tableau range: \n"); 
	printf("le nombre de noeud de l'arbre est :  %d\n",Taille(&K));
	
	printf("la profondeur de l'arbre est de: %d \n", Profondeur(&K));
	//Profondeur(&K);
	printf("Tableau range: ");
	
	
	for (i=0; i<=p; i++)
	{
		table[i] = rand()%100000;
	}
  	quicksort(table,0,p-1);
  	 
  	/*printf("Tableau range: ");
  	for(i=0;i<p;i++)
    	printf(" %d \n",table[i]);
	*/
	printf("Tableau range: ");
	for(i=0;i<p;i++) {	
	tab = table[i];	
	
	Ajouter(&N, tab);
	}





return 0;	
}
