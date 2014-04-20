#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <functional>

void gen( int array[], std::size_t n, int /*type*/, int value )
{ 
    std::cout << "value: " << value << ' ' ;
    std::fill_n( array, n, value ) ; 
}

void gen( int array[], std::size_t n, int type )
{ 
    if( type == 'E' )
    {
        std::cout << "random " ;
        gen( array, n, type, std::rand() ) ;
    }
    
    else
    {
        std::generate_n( array, n, std::rand ) ;
        
        if( type == 'A' ) std::sort( array, array+n ) ;
        
        else if( type == 'D' ) std::sort( array, array+n, std::greater<int>() ) ;
    }
}


int main( int argc, char* argv[] )
{
    std::srand( std::time(nullptr) ) ;
    
    if( argc == 3 || argc == 4 )
    {
        try
        {
            // http://en.cppreference.com/w/cpp/string/basic_string/stol
            const int how_many = std::stoi( argv[1] ) ;
            std::cout << "how many: " << how_many << ' ' ;
            
            if( how_many > 0 )
            {
                const char type = std::toupper( argv[2][0] ) ;
                std::cout << "type: '" << type << "' " ;
                
                const std::string valid_types = "ADRE" ;
                if( valid_types.find(type) != std::string::npos )
                {
                    std::vector<int> array( how_many ) ;
                    
                    if( type == 'E' && argc == 4 ) gen( &array.front(), array.size(), type, std::stoi( argv[3] ) ) ;
                    else gen( &array.front(), array.size(), type ) ;

                    std::cout << "\ngenerated sequence: " ;
                    for( int v : array ) std::cout << v << ' ' ;
                    std::cout << "\n-------------\n" ;
                    return 0 ;
                }
            }
        }
        
        catch( const std::exception& ) { std::cerr << "error in command line args\n" ; }
        return 1 ;
    }
    
    std::cerr << "error in command line args\n" ;
}

