#include <iostream>
using namespace std;

int main()
{
   int n;
   int dato;
   int max;
   cout << "Quanti sono i dati? ";
   cin >> n;
   for (int i=1; i<=n; i++) {
       cout << "Inserisci il "<< i << " . dato: ";
       cin >> dato;
       if (i==1)max = dato;
       if (dato > max) max = dato;
   }
    cout << "Il massimo valore e' "<< max << endl;
   
   return 0;
}