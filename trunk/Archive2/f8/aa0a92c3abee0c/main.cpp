#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>


//sum of 1 <= n <= 1e4
//s(n,1e2)
int main()
{
    std::vector<int> primes(1,2);
    
    {
        const int largest = 1e2;
        const int sqrt = 10;
        std::vector<bool> sieve(largest, true);
        sieve.at(0) = false;
        sieve.at(1) = false;
        for(int i = 2; i <= sqrt; ++i)
        {
            if(!sieve.at(2))
            {
                continue;
            }
            
            for(int j = i * i; j < largest; j += i)
            {
                sieve.at(j) = false;
            }
        }
        for(int i = 3; i < largest; i += 2)
        {
            if(sieve.at(i))
            {
                primes.push_back(i);
            }
        }
    }
    
    using boost::multiprecision::cpp_int;
    const cpp_int max = 10000;
    cpp_int sum = 0;
    for(int i = 1; i <= max; ++i)
    {
        cpp_int temp = i*i*i*i*i*i*i*i*i*i*i*i*i*i*i+1;
        
        for(const auto &it: primes)
        {
            if(temp % it == 0)
            {
                sum += it;
            }
        }
    }
    
    std::cout << "SUM: " << sum << std::endl;
}