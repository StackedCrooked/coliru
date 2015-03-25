#include <stdio.h> 
#include <stdlib.h>
 
int principal ( void ) 
{ 
    ARCHIVO * fp = fopen ( "test.txt" , "r" ) ; 
    si ( ! fp )  { 
        perror ( "apertura de archivos no" ) ; 
        volver  EXIT_FAILURE ; 
    }
 
    int c ;  // nota: int, no char, necesaria para manejar EOF 
    mientras que  ( ( c =  fgetc ( fp ) )  ! =  EOF )  {  // bucle al leer el archivo de E / S estándar CI 
       putchar ( c ) ; 
    }
 
    si  ( FERROR ( fp ) ) 
        puts ( "error de E / S al leer" ) ; 
    lo demás  si  ( feof ( fp ) ) 
        puts ( "Fin de archivo alcanzaron con éxito" ) ;
 
    fclose ( fp ) ; 
}