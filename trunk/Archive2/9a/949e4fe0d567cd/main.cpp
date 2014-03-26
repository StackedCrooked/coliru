#include <stdio.h>
#include <stdlib.h>

int main() // can be void if using tc
{
    const char* DATABASE_FILE = "foo.txt";
    const int MAX_CHAR = 100;

    char szTemp[ MAX_CHAR ];

    puts( "Enter your name : " );
    fgets( szTemp, MAX_CHAR, stdin ); // get the whole line (including spaces)

    FILE* out_file; // pointer to file

    // open the file
    out_file = fopen( DATABASE_FILE, "w+"); // "w" means "write"

    if( out_file == NULL ) // if opening failed
        exit( EXIT_FAILURE );

    // write the content of szTemp to file
    fprintf( out_file, "%s\n", szTemp ); // http://www.cplusplus.com/reference/cstdio/fprintf/

    fclose( out_file ); // close the file
}