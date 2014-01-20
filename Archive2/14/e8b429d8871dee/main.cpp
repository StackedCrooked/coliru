# Include <vector> 
# include <deque> 
# include <iostream> 
# include <iterator> 
# include <algorithm> 
int principale ( ) 
{ 
    std :: vecteur < int > v { 1 , 2 , 3 , 4 , 5 } ; 
    std :: deque < int > d ; 
    std :: copie ( v commencer ( ) , v fin ( ) ,
              std :: front_insert_iterator < std :: deque < int >> ( d ) ) ;  / / ou std :: front_inserter (d) 
    pour ( int n : d ) 
        std :: cout  << n <<  '' ; 
    std :: cout  <<  " \ n " ; 
}