#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    //primes less than 1 million not the first 1 million
    const unsigned max = 1e6; //1 million
    const unsigned sqrt = std::sqrt( max );
    
    std::vector<bool> primes( max, true ); //supposedly you can fit 8 bool into 1 byte if its in a vector
    //though if its less than 8 it will still be 1 byte
    //container will store 3->1e6-1
    
    for( unsigned i = 3; i < sqrt; i += 2 )//odds only //index 0 = 3 , index 1 = 5 , index 2 = 7, ect...
    //some cases you may want <= sqrt also if say the sqrt is 7.3 it will round down to 7 but you will want to check for 7s.
    {
        if( primes.at((i>>1)-1) )//if current index is a prime
        {
            for( unsigned j = ((i * i) >>1) - 1; j <= max; j += i )//incremting by 2 * i really since I removed all evens already
            {
                std::cout << j << ' ';
                primes.at(j) = false; //could use an if statement so you don't replace
                //ones that are already set but may slow down speed
            }
        }
    }
    
    unsigned sum = 2; //2 is prime
    for( unsigned i = 0; i < primes.size(); ++i )
    {
        sum += i * 2 + 3;
    }
    
    std::cout << "The sum of primes below 1 million are: " << sum << std::endl;
}