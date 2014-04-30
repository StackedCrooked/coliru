# Include <stdio.h> 
# include <stdlib.h> 
# include <string.h>
 
int principal ( ) 
{ 
    charlas A [ ]  =  "Haga la prueba." ; 
    Char  * B =  malloc ( strlen ( A )  +  1 ) ; 
    strcpy ( B, A ) ; 
    A [ 0 ]  =  'M' ; 
    printf ( " A =% s ​​\ n B =% s ​​" , A, B ) ;
 
    devolver  0 ; 
}