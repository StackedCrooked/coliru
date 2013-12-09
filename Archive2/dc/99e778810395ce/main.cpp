# Include <stdio.h>
 
int principales ( ) 
{ 
    printf ( "Cuerdas: \ n " ) ; 
    const  caracteres * s =  "Hello" ; 
    printf ( " \ t ..% 10s \ n \ t ..%-10s \ n \ t %. * s . \ n " , s, s, 10 , s ) ;
 
    printf ( "Personajes: \ t % c%% \ n " , 65 ) ;
 
    printf ( "Los números enteros \ n " ) ; 
    printf ( "Decimal: \ t % i% d% i% i 0,6% 0,0% i + i% u \ n " , 1 , 2 , 3 , 0 , 0 , 4 , - 1 ) ; 
    printf ( "Hexadecimal: \ t % x% x% x% # x \ n " , 5 , 10 , 10 , 6 ) ; 
    printf ( "octal: \ t % s% # o% # o \ n " , 10 , 10 , 4 ) ;
 
    printf ( "coma flotante \ n " ) ; 
    printf ( "Redondeo: \ t % f% .0 f% .32 f \ n " , 1.5 , 1.5 , 1.3 ) ; 
    printf ( "Relleno: \ t % 05.2f% .2 f% 5.2f \ n " , 1.5 , 1.5 , 1.5 ) ; 
    printf ( "Científico: \ t % E% e \ n " , 1.5 , 1.5 ) ; 
    printf ( "Hexadecimal: \ t % a% A \ n " , 1.5 , 1,5 ) ; 
}