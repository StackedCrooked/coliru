#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main()
{
    const char* const path = "data.txt" ;
    
    // create test file
    { 
        std::ofstream(path) << "562\n"
        "444223.123321 312233.31222 3232323.31122\n"
        "332231.323223 333232.32323 3232322.32233\n" ;
    }

    std::ifstream file(path) ; // open file for input
    
    if( !file.is_open() ) // verify that the file was opened
    {
        std::cerr << "could not open input file\n" ;
        return EXIT_FAILURE ;
    }
    
    int seed ;
    if( file >> seed ) 
    {
        if( seed == 0 ) 
        {
            std::clog << "using curent time as seed " ;
            seed = std::time(nullptr) ;
        }
        std::cout << "seed: " << seed << '\n' ;
        std::srand(seed) ;

        double mb1; //mass body 1
        double xc1; //x coordinate 1
        double yc1; //y coordinate 1

        double mb2; //mass body 2
        double xc2; //x coordinate 2
        double yc2; //y coordinate 2

        if( file >> mb1 >> xc1 >> yc1 >> mb2 >> xc2 >> yc2 )
        {
            std::cout << std::fixed << "body 1: mass " <<  mb1 << "  location ( " << xc1 << ", " << yc1 << " )\n"
                                    << "body 2: mass " <<  mb2 << "  location ( " << xc2 << ", " << yc2 << " )\n" ;

            // ...
        }
        
        else // file >> mb1 >> xc1 >> yc1 >> mb2 >> xc2 >> yc2 failed
        {
            std::cerr << "badly formatted input on subsequent lines\n" ;
            return EXIT_FAILURE ;
        }
        
    }
        
    else // file >> seed failed
    {
        std::cerr << "badly formatted input on line one\n" ;
        return EXIT_FAILURE ;
    }
}