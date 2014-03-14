#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

/* Structure représentant une transition */
typedef struct {
    int source;     // etat source
	char symbol;    // symbole de la transition
	int dest;       // etat destination
} transition;

/* Structure représentant un automate */
struct automate_t {
	char alphabet[256];  // alphabet
	int nb_states;       // nombre d'états
	int initial;        // l'etat intial 
	int final;          // L'etat final
	int nb_transitions;        // Le nombre de transitions
	transition *table;    // La table de transition
	int nb_alphabet; // nb alphabet
};

// Affiche quelques informations sur l'automate p
void affiche (struct automate_t p) {
	int i;  
	printf("\n- l'alphabet de l'automate est le suivant :");
	
	for(i=0;i<2;i++){    
		printf("%c ",p.alphabet[i]);
    }  
		printf("\n- L'automate possede %d etats\n", p.nb_states);
		printf("- l'etat initial est: %d\n", p.initial);
		printf("- L'etat final est: %d\n", p.final);
		printf("- Il y a %d transitions\n\n", p.nb_transitions);

		for (i = 0; i < p.nb_transitions; i++) {
			printf("\tTransition %d : %d -> %d [%c]\n",i, p.table[i].source, p.table[i].dest, p.table[i].symbol);
		}

                     
}
// construction de la table des bords
int* table_des_bords(char* texte,int m){
	   
	int j=0,i;
	int* bord_u = (int*)malloc((m+1)*sizeof(int));
	bord_u[0]=-1;
	bord_u[1]=0;
	 
	
	for(i=2;i<=m;i++){
		while((texte[j] != texte[i-1]) && (j>=0))
			j=bord_u[j];
				    
		j=j+1;
		bord_u[i]=j;
	}

return bord_u;
}
// recuperer l'indice de la table d'une transition donnée
int recuperer_indice_table(int etat,int r,struct automate_t A){
	int t=0;

	while ((A.table[t].source != etat) || (A.table[t].symbol != A.alphabet[r]))
		t++;

return t;
}

//construction de l'automate suivant l'algo vu en cours
struct automate_t calcul_automate(char * texte, int n){

	int* bord_u=table_des_bords(texte,n);
	int m=1;
	int l,z,j,r,t;
	int s=1;
	int i=0;
	int q=0;
	// déclarer un automate
	struct automate_t automate ;
	//allocation dynamique de l'automate du tableau de transition qui est dans automate
	automate.table=(transition*)malloc((automate.nb_transitions)*sizeof(transition));

	/* récuperer l'alphabet d'un mot donnée qu'on stockera dans le tableau automate.alphabet[256] 
	et au meme temps compter le nombre d'alpahabet ce qui peux nous servire par la suite*/
	
	automate.alphabet[0]=texte[0];
	automate.nb_alphabet=1;
	while(m<n){
			l=0;
			while((automate.alphabet[l] != texte[m]) && (l<automate.nb_alphabet)){   
					l++;                                             
					if (l == automate.nb_alphabet)  {
							automate.alphabet[l]=texte[m];
							automate.nb_alphabet=automate.nb_alphabet+1;
					}
				}
			m++;
	}



	// initionalisation des champs de la structure automate
	automate.nb_states=n+1;               
	automate.nb_transitions=(n+1)*automate.nb_alphabet;
	automate.final=n; //marquer n+1 comme état final 
	automate.initial=0; //marquer 0 comme état initial

	// 0.u1=1 on commence par remplire les champs pour l'etat 0 en lisant u1
	automate.table[0].source=0;
	automate.table[0].dest=1;
	automate.table[0].symbol=texte[0];

	//ici on remplis les champs pour l'etat 0 en lisant (a appartient a l'ensemble des mots) si a != u1 alors 0.a=0
	
	while (i<automate.nb_alphabet){
		if (automate.alphabet[i] != texte[0]){
			automate.table[s].source=0;
			automate.table[s].dest=0;
			automate.table[s].symbol=automate.alphabet[i];
			s++;
		}
		i++;

	/*ici on remplis les champs pour toutes les transitions qui sont les lettres du mot il suffis de passer d'etat a l'etat suivant 
	en inscivant le symbol du mot a cette posittion */
	}

	for(z=0;z<n-1;z++){
		automate.table[z+automate.nb_alphabet].source=z+1;/* z+nb_alphabet car il faut qu'on commence de la table en prenant en compte 
        les tables qui ont été remplis au par avant, il se trouve que ses tables c'est toujours ce qu'on a fais pr 0 
        donc nombre d'alphabet + l'indice z */
		automate.table[z+automate.nb_alphabet].dest=z+2;
		automate.table[z+automate.nb_alphabet].symbol=texte[z+1];

	}


	//ici on remplis les champs pour chaque alphabet a != uj, on lui met les transitions p.a=bord[p].a
	                                           
	for(j=1;j<n;j++){
		for(r=0;r<automate.nb_alphabet;r++){
			if (automate.alphabet[r] != texte[j]){
				automate.table[j+n].source=j;
				t=recuperer_indice_table(bord_u[j],r,automate);
				automate.table[j+n].dest=automate.table[t].dest;
				/*j+n car position du moment plus les tables eja traité qui 
				sont jusque la egale a n sachant que la table commence a 0*/
				automate.table[j+n].symbol=automate.alphabet[r];
			}

		}
	}

	//ici on fais l'etat final, pour tout alphabet a appartenant a l'ensemble des alphabet on met n.a=bord[n].a 
	
	while (q<automate.nb_alphabet)
	{
		automate.table[q+j+n].source=n;
		t=recuperer_indice_table(bord_u[n],q,automate);
		automate.table[q+j+n].dest=automate.table[t].dest;
		automate.table[q+j+n].symbol=automate.alphabet[q];
		q++;

	}

return automate;
}

//calculer le nombre d'occurence du motif reconnu par notre automate dans le mot de longeur n
int algo(struct automate_t automate, char* mot,int n){
    int occ=0;
    int etat_courant=0;
    int i,m;     
    
  
    
	for(i=0;i<n;i++){ // en partant de chanque etat en lisant chaque alphabet on teste si egale au mot
		m=0;
		etat_courant=recuperer_indice_table(etat_courant,m,automate);

		while (automate.table[etat_courant].symbol != mot[i] && m < automate.nb_alphabet){
			m=m+1; 
			etat_courant=recuperer_indice_table(automate.table[etat_courant].source,m,automate);
		}      
		etat_courant=automate.table[etat_courant].dest;/*prochain etat a tester c'est l'extremite de la transition (dest)
		fonction qui recupere l'indice ou se trouve notre etat */
		printf("\n \t l'etat courant est %d",etat_courant); 

		if(etat_courant == automate.final)                         
			occ=occ+1;                                                                                          
     
     
	}

return occ;
}                           
int main(void){
     
   
	char* motif= (char*)"abaab"; 
	char* mot=(char*)"abaabaabaab";
	int* bords=table_des_bords(motif,5);
	int i;
	int occ;

	printf("- voici la table des bords :");

	for(i=0;i<=5;i++){
		printf("%d ", bords[i]);
	}
	struct automate_t automate=calcul_automate(motif,5);
	printf("\n- le nb d'alphabet est de %d",automate.nb_alphabet);	                                                                                            //(fonction recuper_indice_table marche bien)
	affiche(automate);
	printf("\nDeroulement de l'algo qui compte le nombre d'occurence du motif dans le mot : \n");
	occ=algo(automate,mot,11);
	printf("\n\nLE NOMBRE D'OCCURENCE DU MOTIF %s DANS LE MOT %s EST DE : %d\n",motif,mot,occ);
	printf("\n");
	
	free(bords);
   
	
	//system("PAUSE");
return 0;
}
