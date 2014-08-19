# include <iostream>
 
int principal ( )  
{ 
    para  ( int i =  0 ; i <  10 ; i ++ )  { 
        si  ( i ! =  5 )  continuar ; 
        std :: cout  << i <<  "" ;        // esta declaración se salta cada vez i! = 5 
    }
 
    std :: cout  <<  " \ n " ;
 
    para  ( int j =  0 ; j <  2 ; j ++ )  { 
        para  ( int k =  0 ; k <  5 ; k ++ )  {    // sólo este bucle se ve afectada por continuar 
            si  ( k ==  3 )  continuar ; 
            std :: cout  << j << k <<  "" ;  // esta declaración se salta cada vez k == 3 
        } 
    } 
}