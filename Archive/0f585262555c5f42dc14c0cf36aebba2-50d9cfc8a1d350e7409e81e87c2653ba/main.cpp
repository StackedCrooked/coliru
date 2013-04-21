#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int n, un, c=0;
  /*
  * inizializzo d a zero perchè devo accomularvi i valori delle cifre dispari mano
  * a mano che le trovo. 
  *
  * pc (peso cifra: è la potenza di dieci per cui moltiplico la cifra dispari) 
  * è inizializzato a zero perchè la prima volta in cui si entra
  * nell'if devo elevare dieci alla zero, successivamente lo incremento.
  */
  cout << "Inserire un numero intero positivo: "; 
  cin >> n;
  
  /*
  * Il ciclo while scorre ogni cifra del mio numero, n infatti rappresenta ciò
  * che rimane del numero ad ogni ciclo.
  */
  while( n>0 ){
    //memorizzo un: la cifra delle unità di n
    un = n % 10;
    
    //tolgo da n la cifra delle unità
    n /= 10;
    // stampo un
    cout << un << "\n";
    // siccome devo contare il numero di cifre incremento c di 1
    c++;
    
  }
  // stampo il numero ottenuto
  cout << "\nIl numero di cifre del numero è " << c;
  return 0;
}