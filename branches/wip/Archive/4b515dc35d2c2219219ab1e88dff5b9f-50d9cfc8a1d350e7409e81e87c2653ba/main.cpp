#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int n = 47632, cifra, numeroCifre=0, x;
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
  cout << "\n"; 
  x = n;
  
  /*
  * Il ciclo while scorre ogni cifra del mio numero, n infatti rappresenta ciò
  * che rimane del numero ad ogni ciclo.
  */
  while( x>0 ){    
    //tolgo da n la cifra delle unità
    x /= 10;
    // siccome devo contare il numero di cifre incremento numeroCifre di 1
    numeroCifre++;    
  }
  
  /*
  * eseguo un ciclo for che iniziando da ( numeroCifre - 1 ), arriva a zero 
  * decrementando c di uno in uno
  */
  for(int c = numeroCifre-1; c>=0; c--){
      /*
      * Trovo la cifra più a sinistra dividendo n per la potenza di dieci 
      * con indice c
      */
      cifra = n / pow(10, c);
      
      // stampo la cifra
      cout << cifra << "\n";
      // elimino il numero più a destra in n
      n -= cifra * pow(10, c);
  }
  
    // stampo il numero ottenuto
  cout << "\nIl numero di cifre del numero è " << numeroCifre << "\n";
  
  return 0;
}