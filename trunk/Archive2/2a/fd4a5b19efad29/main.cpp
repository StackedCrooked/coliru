#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

enum Modes
{
    MOD2 = 1 << 0,
    MOD3 = 1 << 1,
    MOD5 = 1 << 2,
    MOD7 = 1 << 3,
    MOD9 = 1 << 4
};

int main()
{
    long long int mod2 = 0, mod3 = 0, mod5 = 0, mod7 = 0, mod9 = 0;
    
    auto t1 = std::chrono::high_resolution_clock::now();
    for ( long long int i = 0; i < 1000000; ++i )
    {  
        if ( i & 2 )
            ++mod2;
        else if ( i & 3 )
            ++mod3;
        else if ( i & 5 )
            ++mod5;
        else if ( i & 7 )
            ++mod7;
        else if ( i & 9 )
            ++mod9;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count() << std::endl;

    std::cout << mod2 << std::endl;
    std::cout << mod3 << std::endl;
    std::cout << mod5 << std::endl;
    std::cout << mod7 << std::endl;
    std::cout << mod9 << std::endl;
    
    std::cout << "-------------------------------" << std::endl;

    mod2 = 0, mod3 = 0, mod5 = 0, mod7 = 0, mod9 = 0;
    
    t1 = std::chrono::high_resolution_clock::now();
    for ( long long int i = 0; i < 1000000; ++i )
    {  
        std::vector< bool > vect = { i & 2, i & 3, i & 5, i & 7, i & 9 };
        
        int intValue( 0 );
        for ( int j = 0; j < vect.size(); ++j )
            if ( vect[ j ] )
            {
                intValue =  1 << j;
                break;
            }
            
        switch ( intValue )
        {
            case MOD2: ++mod2; break;
            case MOD3: ++mod3; break;
            case MOD5: ++mod5; break;
            case MOD7: ++mod7; break;
            case MOD9: ++mod9; break;
            
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count() << std::endl;


    std::cout << mod2 << std::endl;
    std::cout << mod3 << std::endl;
    std::cout << mod5 << std::endl;
    std::cout << mod7 << std::endl;
    std::cout << mod9 << std::endl;
}
