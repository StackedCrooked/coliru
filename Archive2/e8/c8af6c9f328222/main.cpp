# include <iostream> 
# include <cstdlib>
 
int principal ( ) 
{ 
    const  de char  * str1 =  "42" ; 
    const  de char  * str2 =  "3.14159" ; 
    const  caractere  * str3 =  "31337 com as palavras" ; 
    const  de char  * str4 =  "palavras e 2" ;
 
    int num1 = std :: atoi ( str1 ) ; 
    int num2 = std :: atoi ( str2 ) ; 
    int num3 = std :: atoi ( str3 ) ; 
    int NUM4 = std :: atoi ( str4 ) ;
 
    std :: cout  <<  "std :: atoi ( \ " "  << str1 <<  " \ " ) é "  << num1 <<  ' \ n ' ; 
    std :: cout  <<  "std :: atoi ( \ " "  << str2 <<  " \ " ) é "  << num2 <<  ' \ n ' ; 
    std :: cout  <<  "std :: atoi ( \ " "  << str3 <<  " \ " ) é "  << num3 <<  ' \ n ' ; 
    std :: cout  <<  "std :: atoi ( \ " "  << str4 <<  " \ " ) é "  << NUM4 <<  ' \ n ' ; 
}