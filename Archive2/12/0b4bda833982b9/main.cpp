#include <iostream>
#include <string.h>

    int  nbltra=3;
	int  lgligne=7;
	int  nblbas=3;
	
	char TOee[99][7];
	long TOee_id[99];
	char TADV[99][7];
	
	int  taille_max_tab=99;
	int  nb_del;
	long Tab_del[99];
	int  nb_ajou;
	int  Tab_ajou[99];
	int  nb_trouv;
	long Tab_trouv[99];


void actadv_compar_liste_adv_oee_courant_godet (int  nb_ltra,
                int  lg_ligne,
                char *ps_TADV,
                int  nb_lbas,
                char *ps_TOee,
                long *ps_TOee_id,
                int  taille_max_tab,
                int  *nb_del,
                long *ps_del,
                int  *nb_ajou,
                int  *ps_ajou,
                int  *nb_trouv,
                long  *ps_trouv)
{


 int  *t_del;
 int  *t;
 int  i,j ;
 int CDOS_LG_TRA_SX=7;
 /* allocation du tableau t de taille taille_max_tab */
 t = (int *) malloc (taille_max_tab * sizeof (int) ) ;
 if (t == 0)
 {
      std::cout << "FATAL ERROR" << std::endl;

 }
 for (t_del=t; t_del<t+nb_lbas; t_del++) * (t_del) =1 ;

 *nb_ajou=0 ;
 *nb_del=0 ;
 *nb_trouv=0 ;

 for (i=0; i<nb_ltra; i++)
 {
  j=0;
                    /*printf("ADV : %s \n", (char *)(ps_TADV+i*lg_ligne));*/

  while ( (j<nb_lbas) && strncmp ( (ps_TOee+j*CDOS_LG_TRA_SX), (ps_TADV+i*lg_ligne), (lg_ligne-1) ) )
  {
          /*printf("OEE : %s \n", (char *)(ps_TOee+j*CDOS_LG_TRA_SX));*/
   j++;
  }
  if (j == nb_lbas)
  {
   *(ps_ajou+ (*nb_ajou) )=i ;
   *nb_ajou=*nb_ajou+1 ;
  }
  else if (j < nb_lbas)
  {
   t[j]=0 ;
   *(ps_trouv+ (*nb_trouv) )=j ;
   *nb_trouv=*nb_trouv+1 ;
  }
 }

 i=0 ;
 while (i < nb_lbas)
 {
  if (t[i] == 1)
  {
   * (ps_del+ (*nb_del) ) =* (ps_TOee_id+i);
   *nb_del=*nb_del+1;
  }
  i++ ;
 }
 free (t) ;

} 

    
int main()
{

    strcpy(TOee[0],"said11");
	strcpy(TOee[1],"said31");
	strcpy(TOee[2],"said11");
    
	TOee_id[0]=11;
	TOee_id[1]=12;
    TOee_id[2]=111;
	
	strcpy(TADV[0],"said11");
	strcpy(TADV[1],"said31");
	strcpy(TADV[2],"said31");

	for(int i = 0; i < taille_max_tab ; i++){
		Tab_del[i]=-1;
		Tab_ajou[i]=-1;
		Tab_trouv[i]=-1;
	}

	actadv_compar_liste_adv_oee_courant_godet(nbltra,lgligne,(char *)TADV,nblbas,(char *)TOee,TOee_id,taille_max_tab,&nb_del,Tab_del,&nb_ajou,Tab_ajou,&nb_trouv,Tab_trouv);
	    
    for(int i=0; i<nb_trouv;i++){
        printf("OEE %ld, Id: %ld , Value:'%s' \n", *(Tab_trouv+i), TOee_id[*(Tab_trouv+i)], TOee[*(Tab_trouv+i)] );
    }
}
