#include <iostream>
 
plantilla < nombre de tipo T > 
void f ( T s ) 
{ 
    std :: cout  << s <<  " \ n " ; 
}
 
int principal ( ) 
{ 
    f < doble > ( 1 ) ;  // instancia y pide f <doble> (doble) 
    f <> ( 'a' ) ;  // instancia y pide f <char> (char) 
    f ( 7 ) ;  // instancia y llama f <int> (int) 
    void  ( * ptr ) ( std :: string )  = f ;  // instancia f <string> (cadena) 
}