#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <stdint.h>
#include <chrono>

static inline unsigned long long rdtsc()
{
    unsigned long long d; __asm__ __volatile__ ("rdtsc" : "=A" (d) ); return d;
}

int main()
{
    const int numElements = 10;

    { // Test with chrono
    std::vector< int > vect( numElements );
    std::list< int > list( numElements );

    auto l1 = std::chrono::high_resolution_clock::now();
    auto listIter = std::next( list.begin(), 5 );
    list.insert( listIter, 1 );
    auto l2 = std::chrono::high_resolution_clock::now();

    auto v1 = std::chrono::high_resolution_clock::now();
    vect.insert( vect.begin() + 5, 1 );
    auto v2 = std::chrono::high_resolution_clock::now();

    std::cout << "Chrono time: " << "Vector: " << std::chrono::duration_cast<std::chrono::nanoseconds>( v2 - v1 ).count() << "\t" << "List: " << std::chrono::duration_cast<std::chrono::nanoseconds>( l2 - l1 ).count() << std::endl;
    }

    { // Test with rdtsc
    std::vector< int > vect( numElements );
    std::list< int > list( numElements );

    auto l1 = rdtsc();
    auto listIter = std::next( list.begin(), 5 );
    list.insert( listIter, 1 );
    auto l2 = rdtsc();

    auto v1 = rdtsc();
    vect.insert( vect.begin() + 5, 1 );
    auto v2 = rdtsc();

    std::cout << "rdtsc TSC in EDX:EAX: " << "Vector: " << v2 - v1 << "\t" << "List: " << l2 - l1 << std::endl;
    }

    return 0;
}
