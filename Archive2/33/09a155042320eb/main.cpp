#include <stdio.h>
#include <string.h>

int countWords( char texto[], int pos )
    {
     int cont;

     cont = 0;

     if( texto[ pos ] != '.' )
        {
         cont = countWords( texto, pos + 1 );

         if( texto[ pos ] == ' ' )
            cont++;
        }

     return ( cont );
    }


int enxii()
    {
     char frase[] = "hola mundo.";

     int words;

     words = ( frase[ 0 ] != '.' )? ( 1 + countWords( frase, 0 ) ) : ( 0 );

     printf("\nLa cantidad de palabras es: %i\n\n", words );

     return ( 0 );
    }

int main()
{
    enxii();
}
