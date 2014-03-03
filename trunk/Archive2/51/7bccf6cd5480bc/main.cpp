#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    //primes less than 1 million not the first 1 million
    const unsigned max = 1e6; //1 million
    const unsigned sqrt = std::sqrt( max );
    
    std::vector<bool> primes( max/2 , true ); //supposedly you can fit 8 bool into 1 byte if its in a vector
    //though if its less than 8 it will still be 1 byte
    //container will store 3->1e6+1
    
for( unsigned i = 3; i < sqrt; i += 2 )
    {
        if( primes[(i>>1)-1] )
        {
            for( unsigned j = ((i * i) >>1) - 1; j < max; j += i )
            {
                primes.at((j>>1)) = false; //could use an if statement so you don't replace
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