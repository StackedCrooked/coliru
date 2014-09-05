#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

enum Modes
{
    MOD13 = 1 << 0,
    MOD17 = 1 << 1,
    MOD23 = 1 << 2,
    MOD29 = 1 << 3,
    MOD37 = 1 << 4
};

int main()
{
    long long int mod13 = 0, mod17 = 0, mod23 = 0, mod29 = 0, mod37 = 0;
    
    auto t1 = std::chrono::high_resolution_clock::now();
    for ( long long int i = 0; i < 1000000; ++i )
    {  
        if ( i % 13 == 0 )
            ++mod13;
        else if ( i % 17 == 0 )
            ++mod17;
        else if ( i % 23 == 0 )
            ++mod23;
        else if ( i % 29 == 0 )
            ++mod29;
        else if ( i % 37 == 0 )
            ++mod37;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count() << std::endl;

    std::cout << mod13 << std::endl;
    std::cout << mod17 << std::endl;
    std::cout << mod23 << std::endl;
    std::cout << mod29 << std::endl;
    std::cout << mod37 << std::endl;
    
    std::cout << "-------------------------------" << std::endl;

    mod13 = 0, mod17 = 0, mod23 = 0, mod29 = 0, mod37 = 0;
    
    t1 = std::chrono::high_resolution_clock::now();
    for ( long long int i = 0; i < 1000000; ++i )
    {  
        std::vector< bool > vect = { i % 13 == 0, i % 17 == 0, i % 23 == 0, i % 29 == 0, i % 37 == 0 };
        
        int intValue( 0 );
        for ( int j = 0; j < vect.size(); ++j )
            if ( vect[ j ] )
            {
                intValue =  1 << j;
                break;
            }
            
        switch ( intValue )
        {
            case MOD13: ++mod13; break;
            case MOD17: ++mod17; break;
            case MOD23: ++mod23; break;
            case MOD29: ++mod29; break;
            case MOD37: ++mod37; break;
            
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count() << std::endl;


    std::cout << mod13 << std::endl;
    std::cout << mod17 << std::endl;
    std::cout << mod23 << std::endl;
    std::cout << mod29 << std::endl;
    std::cout << mod37 << std::endl;
}
