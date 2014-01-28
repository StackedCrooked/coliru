#ifdef __cplusplus

#include <iostream>
#include <string>

int main()
{
    // read and print a number
    std::cout << "Enter the number :\n" ;
    int n ;
    if( std::cin >> n ) std::cout << "you entered: " << n << '\n' ;
    
    // read and print a first name
    std::cout << "Enter your first name :\n" ;
    try
    {
        std::string name ;
        if( std::cin >> name )std::cout << "Hello " << name << '\n' ;
    }
    catch(...) { return 1 ; }
}

#else // C

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    // read and print a number
    puts( "Enter the number : " ) ;
    int n ;
    if( scanf( "%d", &n ) == 1 ) printf( "you entered: %d\n",  n ) ;
    
    // read and print a first name
    size_t sz = 20 ;
    char* name = malloc(20) ;
    if( name == NULL ) return 1 ;

    puts( "please type in your first name: " ) ;
    int c ;
    while( ( c = getchar() ) != EOF )
    {
        if( !isspace(c) )
        {
            ungetc( c, stdin ) ;
            break ;
        }
    }

    size_t pos = 0 ;
    while( ( c = getchar() ) != EOF )
    {
        if( isspace(c) )
        {
            name[pos] = 0 ;
            break ;
        }

        name[pos] = c ;
        if( pos == sz-1 )
        {
            sz *= 2 ;
            char* temp = realloc( name, sz ) ;
            if( temp == NULL )
            {
               free(name) ;
               return 1 ;
            }
            else name = temp ;
        }
        ++pos ;
    }

    printf( "Hello %s\n", name ) ;
    free(name) ;
}

#endif 
