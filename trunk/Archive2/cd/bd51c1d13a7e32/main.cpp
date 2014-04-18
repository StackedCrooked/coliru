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
                    
                    if( type == 'E' )
                    {
                        const int value = argc == 4 ? std::stoi( argv[3] ) : std::rand() ;
                        std::cout << "value: " << value  ; 
                        
                        // http://en.cppreference.com/w/cpp/algorithm/fill_n
                        std::fill_n( array.begin(), how_many, value ) ;
                    }
                         // http://en.cppreference.com/w/cpp/algorithm/generate_n 
                    else std::generate_n( array.begin(), how_many, std::rand ) ;
                    
                    if( type == 'A' ) std::sort( array.begin(), array.end() ) ;
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

