#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>

int main( int argc, char* argv[] )
{
    std::srand( std::time(nullptr) ) ;
    
    if( argc == 3 || argc == 4 )
    {
        try
        {
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
                    
                    if( type == 'E' )
                    {
                        const int value = argc == 4 ? std::stoi( argv[3] ) : std::rand() ;
                        std::cout << "value: " << value  ;  
                        std::fill_n( std::begin(array), how_many, value ) ;
                    }
                    else std::generate_n( std::begin(array), how_many, std::rand ) ;
                    
                    if( type == 'A' ) std::sort( std::begin(array), std::end(array) ) ;
                    else if( type == 'D' ) std::sort( array.rbegin(), array.rend() ) ;
                    
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

