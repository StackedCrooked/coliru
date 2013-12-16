# Include <iostream> 
# include <cstdlib>
 
int principal ( ) 
{ 
    const  caracteres  * cadena1 =  "42" ; 
    const  caracteres  * str2 =  "3.14159" ; 
    const  caracteres  * str3 =  "31337 con las palabras" ; 
    const  carac  * Str4 =  "palabras y 2" ;
 
    int num1 = std :: atoi ( cadena1 ) ; 
    int num2 = std :: atoi ( str2 ) ; 
    int num3 = std :: atoi ( str3 ) ; 
    int num4 = std :: atoi ( str4 ) ;
 
    std :: cout  <<  "std :: atoi ( \ " "  << cadena1 <<  " \ " ) es "  << num1 <<  ' \ n ' ; 
    std :: cout  <<  "std :: atoi ( \ " "  << cad2 <<  " \ " ) es "  << num2 <<  ' \ n ' ; 
    std :: cout  <<  "std :: atoi ( \ " "  << str3 <<  " \ " ) es "  << num3 <<  ' \ n ' ; 
    std :: cout  <<  "std :: atoi ( \ " "  << str4 <<  " \ " ) es "  << num4 <<  ' \ n ' ; 
}