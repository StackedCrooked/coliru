# Include <iostream> 
# include <chrono> 
# include <ctime>
 
dlhý Fibonacciho ( int n ) 
{ 
    ak  ( n <  3 )  return  1 ; 
    návrat Fibonacciho ( n - 1 )  + Fibonacci ( n - 2 ) ; 
}
 
int main ( ) 
{ 
    std :: chrono :: time_point < std :: chrono :: system_clock > začiatok, koniec , 
    začiatok = std :: chrono :: system_clock :: teraz ( ) ; 
    std :: cout  <<  "f (42 ) = "  << Fibonacciho ( 42 )  <<  ' \ n ' ; 
    koniec = std :: chrono :: system_clock :: teraz ( ) ;
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std :: cout  <<  "dokončil výpočet na"  <<  std :: Ctíme ( a end_time ) 
              <<  "Uplynulý čas:"  << . elapsed_seconds počítať ( )  <<  "s \ n " ; 
}