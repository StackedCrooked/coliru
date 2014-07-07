# Include <aleatorio> 
# include <iostream>
 
int principal ( ) 
{ 
    std :: random_device rd ; 
    std :: MT19937 gen ( rd ( ) ) ; 
    std :: uniform_int_distribution <> dis ( 1 , 6 ) ;
 
    para  ( int n = 0 ; n < 10 ;  + + n ) 
        std :: cout  << dis ( GEN )  <<  '' ; 
    std :: cout  <<  " \ n " ; 
}