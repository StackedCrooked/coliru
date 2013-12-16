#include <iostream>
#include <vector>
#include <algorithm>
  
// using namespace std; interdiction formelle d'ecrire using namespace avant d'avoir 10 ans d'experience en c++ !!!!!
  
int main()
{
    // a la rigueur, using de quelques symboles
    using std::cout;
    using std::endl;

    cout << "Bienvenue dans super multiplicateur 1.0 !!" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Entrez un chiffre et la table de ce chiffre vous sera donnée" << endl;
  
    int multiplicateur;
    //std::cin >> multiplicateur;
    multiplicateur = 4;
    
    std::vector<int> table;
    table.reserve( 10 ); // on va push 10 valeurs, autant éviter les réallocations, toujours penser à faire un reserve sur un vector
    
    int compteur = 1; // en attendant des lambda c++14 qui peuvent capturer directement une nouvelle variable dans la closure
    std::generate_n( std::back_inserter( table ), 10, [=]() mutable { return compteur++ * multiplicateur; } );
    
    // affichage
    std::cout << "table de " << multiplicateur << " :"<< std::endl;
    int idx = 1; // again c++14 evite çà
    std::for_each( table.begin(), table.end(), [=]( int v ) mutable { 
        std::cout << multiplicateur << " x " << idx++ <<" = " << v << endl; 
    } );
    
    return 0;
}