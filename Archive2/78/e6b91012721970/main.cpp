#include <iostream>
#include <unistd.h>
#include <cstdlib>

int main( int argc, char* argv[] )
{
    const char* nvalue = "World" ; 
    int tvalue = 1 ;
    
    int c ;
    while( ( c = getopt (argc, argv, "nt:") ) != -1 ) 
    {
        switch(c)
        {
            case 'n':
                if(optarg) nvalue = optarg;
                else std::cerr << "got a nullptr for optarg for -n\n" ;
                break;
            case 't':
                if(optarg) tvalue = std::atoi(optarg) ;
                break;
        }
    }
    
    for( int i = 0 ; i < tvalue; ++i )
       std::cout << '[' << i+1 << "] Hello " << nvalue << "!\n" ;
    std::cout << '\n' ;   
}
