#include <iostream>
#include <iomanip> // pour setprecision()
#include <cmath>   // pour exp()
using namespace std;

int main()
{
  // réduire le format d'affichage
  cout << setprecision(4);

  constexpr double population_initiale(7.0); // population initiale, en milliard d'humains
  constexpr int    annee_depart(2011);       // année initiale
  double taux(1.2);                          // taux de croissance, en %

  int annee(annee_depart);                // année de calcul
  double population(population_initiale); // population mondiale pour l'année 'annee'

  cout << "====---- PARTIE 1 ----====" << endl;
  cout << "Population en " << annee << " : " << population
       << endl;

   //do {
    //cout << "Quelle année (> 2011) ? ";
	//cin >> annee;
	//} while ( annee <= annee_depart );
	annee = 2016;
	
	for (int i = annee_depart + 1; i < annee; i = i + 1) 
    {
	    population = population * exp(taux);
	    cout << "Population en " << i << " : " << population << endl;
	}
	
	cout << "ssadfs";
	return 0;
}