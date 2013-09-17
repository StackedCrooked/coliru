# Include <cstdio> 
# include <clocale> 
# include <ctime> 
# include <cwchar>
 
int main ( ) 
{ 
    / / locale C bude UTF-8 enabled angličtine; 
    / / desatinná bodka bude nemčina 
    / / dátum a čas formátovanie bude
 
    wchar_t str [ 100 ] ; 
    std :: time_t t =  std :: čas ( NULL ) ; 
    std :: wcsftime ( str, 100 , L "%% c" , std :: localtime ( & t ) ) ; 
    std :: wprintf ( L "Číslo:% .2 f \ n Dátum:% ls \ n " , 3.14 , str ) ; 
}