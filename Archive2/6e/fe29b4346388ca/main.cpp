#include <iostream> 
#include <iomanip> 
#include <locale>
 
int principale ( ) 
{ 
    std :: cout . imprégner ( std :: locale ( "en_US.utf8" ) ) ; 
    std :: cout  <<  "Gauche fill: \n "  << std :: left  <<  std:: setfill ( '*' ) 
              <<  std:: setw ( 12 )  <<  - 1.23   <<  ' \n ' 
              <<  std:: setw ( 12 )  <<  std:: hex  <<  std:: showbase  <<  42  <<  ' \n ' 
              <<  std:: setw ( 12 )  <<  std:: put_money ( 123 , true )  <<  " \n \n " ;
 
    std :: cout  <<  "interne fill: \n "  << std :: internal 
              <<  std:: setw ( 12 )  <<  - 1.23   <<  ' \n ' 
              <<  std:: setw ( 12 )  <<  42  <<  ' \n ' 
              <<  std:: setw ( 12 )  <<  std:: put_money ( 123 , true )  <<  " \n \n " ;
 
    std :: cout  <<  "Droite fill: \n "  << std :: right 
              <<  std:: setw ( 12 )  <<  - 1.23   <<  ' \n ' 
              <<  std:: setw ( 12 )  <<  42  <<  ' \n ' 
              <<  std:: setw ( 12 )  <<  std:: put_money ( 123 , true )  <<  ' \n ' ; 
}