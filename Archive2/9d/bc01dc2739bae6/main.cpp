#include <iostream>
#include <math.h>
#include <string>
#include <ctime>

using namespace std;

unsigned int tt;

//define a constant which will be the number of our table index
#define MAX 3

/********************************/
/*        STRUCTURS             */
/********************************/

//struct of a runner : a name and a time done
typedef struct
{
  string nom;
  float tps;
}type_Coureur;


//standar table type
typedef struct
{
  //table of 3 type_Coureur (MAX is define to 3 here)
  type_Coureur Tab[MAX];
  int nb_max;
}Course;

/**********************************/
/*          PROTOTYPES            */
/**********************************/


//init a type_tableau to an number of index used : 0
void ini_tab(Course tab);

/**********************************/
/*      MAIN PROCEDURE            */
/**********************************/

int main()
{
  /* ****** INIT ******* */
  Course c;                             			tt = tt + 1;
  int i;											tt = tt + 1;
  int g;											tt = tt + 1;

													tt = tt + 1;
  ini_tab(c);										tt = tt + 1;

  /* ***** START ******* */
													tt = tt + 3;
  for(i = 0 ; i < 3 ; i++)
  //ask to fill the table by the user for each runner
  {
    cout << "nom/temps coureur" << i << " : "<< endl;	tt = tt + 2;
    cin >> c.Tab[i].nom;							tt = tt + 3;
    cin >> c.Tab[i].tps;							tt = tt + 3;
    c.nb_max = c.nb_max + 1;						tt = tt + 2;
													tt = tt + 2;
  }

  //if nobody have done a better time than the third runner,he win
  g = 2;											tt = tt + 1;

  //if the first runner have been faster than the 2nd
													tt = tt + 5;
  if(c.Tab[0].tps < c.Tab[1].tps)
  {
    //if the first runne have been faster than the 2nd and the 3rd
													tt = tt + 5;
    if(c.Tab[0].tps < c.Tab[2].tps)
    {
      //first runner win
      g = 0;										tt = tt + 1;
    }	
  }
  else
  {
    //else if the 2nd runner have been faster than the 3rd
													tt = tt + 5;
    if(c.Tab[1].tps < c.Tab[2].tps)
    {
      //second runner win
      g = 1;										tt = tt + 1;
    }	
  }

  cout << "Gagnant : " << c.Tab[g].nom << endl;		tt = tt + 3;
  cout << endl;										tt = tt + 1;
  
  cout << "Temps de calcul : " << tt << "t, " << float(clock())/CLOCKS_PER_SEC << "s" << endl;
  cout << "untité tt de temps : " << tt << endl;
  /* ********** END *********** */
  return 0;
}


/*********************************/
/*        SUB-ROUTINES           */
/*********************************/


void ini_tab(Course tab)
//init a type_tableau to an number of index used : 0
{
	tab.nb_max = 0;										tt = tt + 2;
}
