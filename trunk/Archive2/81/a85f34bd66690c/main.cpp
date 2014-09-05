#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void random_animal( char* animal );
void random_body_part( char* bodyPart );
int random_int( int low, int high );
typedef void ( *pfcnRandomWord )( char* word );

int main( int argc, char *argv[] )
{
    int i = 0;
    char thing[80];
    pfcnRandomWord fn;
    srand( ( unsigned )time( NULL ) );
    while( ++i != 10 )
    {
        thing[0] = '\0';
        fn = &random_animal;
        fn( thing );
        strcat( thing, " " );
        fn = &random_body_part;
        fn( thing );
        printf( "%s\n", thing );
    }
    return EXIT_SUCCESS;
}

int random_int( int low, int high )
{
    double d = rand() / ( ( double )( RAND_MAX ) + 1 );
    double s = d * ( ( double )( high ) - low + 1 );
    return ( int )( floor( low + s ) );
}

void random_animal( char* animal )
{
    int n = random_int( 1, 5 );
    switch( n )
    {
        case 1:
            strcat( animal, "horse" );
            break;
        case 2:
            strcat( animal, "cock" );
            break;
        case 3:
            strcat( animal, "gator" );
            break;
        case 4:
            strcat( animal, "bitch" );
            break;
        case 5:
            strcat( animal, "tit" );
            break;
        default:
            strcat( animal, "dog" );
            break;
    }
}

void random_body_part( char* parts )
{
    int n = random_int( 1, 8 );
    switch( n )
    {
        case 1:
            strcat( parts, "head" );
            break;
        case 2:
            strcat( parts, "balls" );
            break;
        case 3:
            strcat( parts, "knees" );
            break;
        case 4:
            strcat( parts, "toes" );
            break;
        case 5:
            strcat( parts, "eyes" );
            break;
        case 6:
            strcat( parts, "ears" );
            break;
        case 7:
            strcat( parts, "mouth" );
            break;
        case 8:
            strcat( parts, "nose" );
            break;
        default:
            strcat( parts, "tits" );
            break;
    }
}