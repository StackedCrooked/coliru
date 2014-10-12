# include <iostream>
 
struct A { 
   double x ; 
} ; 
const A * a = new A { 0 } ;
 
decltype ( um - > x ) x3 ;        // tipo de x3 é dupla (tipo declarado) 
decltype ( ( a - > x ) ) x4 = x3 ;   // tipo de x4 é const double & (expressão lvalue)
 
template  < class T, classe U > 
auto add ( T t, U u )  - > decltype ( t + u ) ;  // tipo de retorno depende de parâmetros do modelo
 
int principal ( )  
{ 
    int i =  33 ; 
    decltype ( i ) j = i * 2 ;
 
    std :: cout  <<  "i ="  << i <<  "," 
              <<  "j ="  << j <<  ' \ n ' ;
 
    auto f =  [ ] ( int a, int b )  - >  int  { 
       voltar a * b ; 
    } ;
 
    decltype ( f ) f2 = f ;  // do tipo de uma função de lambda é único e sem nome 
    i = f ( 2 , 2 ) ; 
    j = f2 ( 3 , 3 ) ;
 
    std :: cout  <<  "i ="  << i <<  "," 
              <<  "j ="  << j <<  ' \ n ' ; 
}