# Include
 
int principal ( vazio ) 
{ 
    printf ( "Strings: \ n " ) ; 
    const  de char * s =  "Olá" ; 
    printf ( " \ t ..% 10s \ n \ t ..%-10s \ n \ t % *. . s \ n " , s, s, 10 , s ) ;
 
    printf ( "Personagens: \ t % c%% \ n " , 65 ) ;
 
    printf ( "inteiros \ n " ) ; 
    printf ( "Decimal: \ t % i 0,6% d% i% i% i 0,0% + i% u \ n " , 1 , 2 , 3 , 0 , 0 , 4 , - 1 ) ; 
    printf ( "Hexadecimal: \ t % x% x% X% # x \ n " , 5 , 10 , 10 , 6 ) ; 
    printf ( "Octal: \ t % o% # o% # o \ n " , 10 , 10 , 4 ) ;
 
    printf ( "ponto flutuante \ n " ) ; 
    printf ( "Arredondando: \ t % f% .0 f% .32 f \ n " , 1.5 , 1.5 , 1.3 ) ; 
    printf ( "Preenchimento: \ t % 05.2f% .2 f% 5.2f \ n " , 1.5 , 1.5 , 1.5 ) ; 
    printf ( "científico: \ t % E% e \ n " , 1.5 , 1.5 ) ; 
    printf ( "Hexadecimal: \ t % a% A \ n " , 1.5 , 1,5 ) ; 
}