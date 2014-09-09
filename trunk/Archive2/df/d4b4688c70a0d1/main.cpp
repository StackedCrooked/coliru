#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

class Test
{
    public:
        Test( long long int& k ) : k_( k ) {}
        ~Test() { ++k_; }
        long long int& k_;
};

void func( long long int& k )
{
    ++k;
}

int main()
{
    long long int j = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    for ( long long int i = 0; i < 100000000; ++i )
    {
        ++j;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count() << std::endl;
    
    long long int k = 0;
    t1 = std::chrono::high_resolution_clock::now();
    for ( long long int i = 0; i < 100000000; ++i )
    {
        Test obj( k );
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count() << std::endl;
    
    std::cout << j << std::endl;
    std::cout << k << std::endl;
}
