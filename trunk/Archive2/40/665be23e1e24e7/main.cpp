//
// File i/o example ( pure C )
//

#include <stdio.h>

#define MAX_CHAR 32

typedef struct tagStudent
{
    int age;
    float mid;
    float final;
    char name[ MAX_CHAR ];
    char surname[ MAX_CHAR ];
} Student;

int main()
{
    FILE* pFile = fopen( "file_test.dat", "r" );
    if( pFile == NULL ) return -1;

    Student st1; // temporary variable

    // format of a file is
    // age mid final name surname
    while( fscanf( pFile,
                   "%d %f %f %s %s",
                   &st1.age, &st1.mid, &st1.final, st1.name, st1.surname ) == 5 ) // if ever fscanf() returns a value
                                                                                    // other than 5, the loop terminates
    {
        printf( "%d %.2f %.2f %s %s",
                st1.age, st1.mid, st1.final, st1.name, st1.surname );
    }

    fclose( pFile );
}
