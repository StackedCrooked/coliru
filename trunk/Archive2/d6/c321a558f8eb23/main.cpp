#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <chrono>
#include <cstdio>
#include <array>

template < typename Scalar, int Size >
struct Test;

template < typename Scalar >
struct Test< Scalar, 1 >
{
    Test() : data({ 99 })  {}
    
    struct Data 
    {
        Scalar a;
    } data;
    static const int size = 1;
};

template < typename Scalar >
struct Test< Scalar, 2 >
{    
    struct Data 
    {
        Scalar a;
        Scalar b;
    } data;
    
    Test() : data({ -1, -2 })  {}
    
    static const int size = 2;
};


int main()
{
 
    
    auto t = std::chrono::system_clock::now();
    std::cout << "seconds since epoch: " << std::chrono::duration_cast< std::chrono::seconds >( t.time_since_epoch() ).count() << std::endl;
    std::cout << "milliseconds since epoch: " << std::chrono::duration_cast< std::chrono::milliseconds >( t.time_since_epoch() ).count() << std::endl;
 
    Test< double, 2 > test;
 
    std::cout << test.data.a << std::endl;
 
}
