#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
   cout << "Inserisci il prezzo: ";
   cin >> a;
   cout << "Inserisci lo sconto: ";
   cin >> b;
   c=a-(a/100*b/100*a);
   cout << "Valore prezzo scontato: " << c;
   return 0;
}