#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int n , un, d=0, pc = 0;
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
    
    // se la cifra ottenuta è dispari entro nell' if
    if( un % 2 != 0 ){
        /*
        * accumulo in d la moltiplicazione della cifra e di dieci alla pc.
        * pow mi restituisce il primo argomento elevato al secondo:
        * es. pow(base_potenza, indice_potenza);
        */
        d += un * pow(10, pc); 
        // incremento pc
        pc++;
    }
  }
  // stampo il numero ottenuto
  cout << "\n" << d;
  return 0;
}
   