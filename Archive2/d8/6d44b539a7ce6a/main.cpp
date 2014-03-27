# Include <studio
# include <límites> 
# include <cstdint> 
# include <cinttypes>
 
int principal ( ) 
{ 
    std :: printf ( "Cuerdas: \ n " ) ;
 
    const  caracteres * s =  "Hello" ; 
    std :: printf ( " \ t ..% 10s \ n \ t ..%-10s \ n \ t ..% * s \ n " , s, s, 10 , s ) ;
 
    std :: printf ( "Personajes: \ t % c%% \ n " , 65 ) ;
 
    std :: printf ( "Los números enteros \ n " ) ; 
    std :: printf ( "Decimal: \ t % i% d% i% i 0,6% 0,0% i + i% u \ n " , 1 , 2 , 3 , 0 , 0 , 4 , - 1 ) ; 
    std :: printf ( "Hexadecimal: \ t % x% x% x% # x \ n " , 5 , 10 , 10 , 6 ) ; 
    std :: printf ( "octal: \ t % o% # o% # o \ n " , 10 , 10 , 4 ) ;
 
    std :: printf ( "coma flotante \ n " ) ; 
    std :: printf ( "Redondeo: \ t % f% .0 f% .32 f \ n " , 1.5 , 1.5 , 1.3 ) ; 
    std :: printf ( "Relleno: \ t % 05.2f% .2 f% 5.2f \ n " , 1.5 , 1.5 , 1.5 ) ; 
    std :: printf ( "Científico: \ t % E% e \ n " , 1.5 , 1.5 ) ; 
    std :: printf ( "Hexadecimal: \ t % a% A \ n " , 1.5 , 1.5 ) ; 
    std :: printf ( "valores especiales: \ t 0/0 =% g 1/0 =% g \ n " , 0 . / 0 , 1 . / 0 ) ;
 
    std :: printf ( "control de ancho variable: \ n " ) ; 
    std :: printf ( "justificado a la derecha de ancho variable: '% * c' \ n " , 5 , 'x' ) ; 
    int r = std :: printf ( : "'% * c' ancho variable justificada izquierda \ n " , - 5 , 'x' ) ; 
    std :: printf ( "los últimos% d caracteres impresos printf () \ n " , r ) ;
 
    / / Tipos de ancho fijo 
    std :: uint32_t val =  std :: numeric_limits < std :: uint32_t > :: max ( ) ; 
    std :: printf ( "Valor más grande de 32 bits es%"  PRIu32  "o% #"  PRIx32  " \ n " , val, val ) ; 
}