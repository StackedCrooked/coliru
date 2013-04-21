#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int a ,b ,d=2;
  /*
  * inizializzo a, b e di con valore due in modo tale che entri nel ciclo la prima volta.
  */
  cout << "inserire un valore numerico per a :";
  cin << a;
  cout << "\ninserire un valore numerico per b :";
  cin << b;
  
  /*
  * finchè la metà della differenza tra a e b è maggiore di zero
  * il ciclo viene eseguito
  */
  while( d/2 > 0 ){
      // stampo a e b uno a fianco dell'altro e vado a capo
      cout << "\n" << a << " ";
      cout << b;      
     
     // assegno a d la differenza tra i due numeri inseriti dall'utente
      if( a>b )
        d = a-b;
      else
        d = b-a;
        
      // incremento a di d/2 e b di d/4
      a += d/2;
      b += d/4;
  }
  
  return 0;
}