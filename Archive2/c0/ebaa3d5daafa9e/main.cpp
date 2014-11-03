#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int alphacmp( const void *a, const void *b ) {
        char **ca = (char**)a;
        char **cb = (char**)b;
        printf("%p, %p", a, ca);
        return -strcmp( *ca, *cb );
}

int main( int argc, char **argv ) {
        int i;
        qsort( argv+1, argc-1, sizeof *argv, alphacmp );
        for( i= 1; i < argc; i++ )
                printf( "%s\n", argv[i] );
}
