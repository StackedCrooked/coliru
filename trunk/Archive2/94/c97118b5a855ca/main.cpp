#include <iostream>
#include<studio.h>

using namespace std;

class Contador{
    public:
     Contador() {cout <<  "Siguiente..."  <<  endl;}
     
};

class  ContadorRegresivo  :  public  Contador{
    public:
    ContadorRegresivo ()  {cout << "Siguiente..."  <<  endl;}
} ;

int main () {
    
    Contador  contador   ;
    system ("pause") ;

 int minutos,  ii;
cout <<  "Cuenta Regresiva"  <<  "n\n"  <<  “Ingrese minutos"  <<  endl;
cin  >>  minutos;

for (int h "minutos-1;  h>- 0;  h- --) {
    ii = 18;
for (int i  =  ii;  1>= 0; 1- -- ) {
    
    cout  <<  h <<  ":"  << I << endl;
    cout  <<  "\a";
    Sleep (100);
    
}    
}


    return 0 ;
}