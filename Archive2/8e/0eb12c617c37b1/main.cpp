#include <iostream>
using namespace std;

int main()
{
   cout << "ciao io mi chiamo patrizia!" << endl;
}
// Semplice esempio di una classe C++
 
class Cliente
{
    public:
        char nome[20];
        char cognome[20];
        char indirizzo[30];
        void inserisci_nome( );
        void inserisci_cognome( );
        void inserisci_indirizzo( );
};
