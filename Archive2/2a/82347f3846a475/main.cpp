 #include <iostream> #include <iostream>
#include <iomanip> #include <iomanip>
#include <string> #include <string>
#include <map> #include <carte>
#include <random> #include <aléatoire>
#include <cmath> #include <cmath>

int main ( ) int main ()
{ {
    // Seed with a real random value, if available // Semences avec une vraie valeur aléatoire, si disponible
    std:: random_device rd ; std :: random_device e;

    // Choose a random mean between 1 and 6 // Choisissez une moyenne aléatoire entre 1 et 6
    std :: default_random_engine e1 ( rd ( ) ) ; std :: e1 default_random_engine (e ());
    std:: uniform_int_distribution < int > uniform_dist ( 1 , 6 ) ; std :: uniform_int_distribution <int> uniform_dist (1, 6);
    int mean = uniform_dist ( e1 ) ; int = uniform_dist moyen (e1);
    std:: cout << "Randomly-chosen mean: " << mean << ' \n ' ; std :: cout << "choisis au hasard moyenne:" << << signifie '\ n';

    // Generate a normal distribution around that mean // Génération d'une distribution normale autour de cette moyenne
    std:: mt19937 e2 ( rd ( ) ) ; std :: mt19937 e2 (e ());
    std:: normal_distribution <> normal_dist ( mean, 2 ) ; std :: normal_distribution <> normal_dist (moyenne, 2);

    std:: map < int , int > hist ; std :: carte <int, int> hist;
    for ( int n = 0 ; n < 10000 ; ++ n ) { for (int n = 0; n <10 000; n ++) {
        ++ hist [ std:: round ( normal_dist ( e2 ) ) ] ; ++ Hist [ std :: ronde (normal_dist (e2))];
    } }
    std:: cout << "Normal distribution around " << mean << ": \n " ; std :: cout << "de distribution normale autour de" signifie << << ": \ n";
    for ( auto p : hist ) { pour (auto p: hist) {
        std:: cout << std:: fixed << std:: setprecision ( 1 ) << std:: setw ( 2 ) std :: cout << std :: fixe << std :: SetPrecision (1) << std :: setw (2)
                  << p. first << ' ' << std:: string ( p. second / 200 , '*' ) << ' \n ' ; << P premier << '' <<. std :: string (p secondes / 200,. '*') << '\ n';
    } }
} } 