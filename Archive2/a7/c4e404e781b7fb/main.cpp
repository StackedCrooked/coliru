#include <stdint.h>
#include <iostream>


template<uint64_t NumberOfStates>
struct NumBitsRequired;


template<>
struct NumBitsRequired<1>
{
    enum { value = 1 };
};


template<>
struct NumBitsRequired<0>
{
    enum { value = 0 };
};

template<uint64_t NumberOfStates>
struct NumBitsRequired
{
    enum { value = 1 + NumBitsRequired<NumberOfStates / 2>::value };
};

template<uint64_t N>
void test()
{
    std::cout << N << " " << NumBitsRequired<N>::value << std::endl;
}


#define TEST(N) 1000'000


int main()
{
    std::cout << "Number_of_states Number_of_bits_required" << std::endl;
    
    test<                        1 >();
    test<                       10 >();
    test<                      100 >();
    test<                     1000 >();
    test<                   10'000 >();
    test<                  100'000 >();
    test<                 1000'000 >();
    test<               10'000'000 >();
    test<              100'000'000 >();
    test<             1000'000'000 >();
    test<           10'000'000'000 >();
    test<          100'000'000'000 >();
    test<         1000'000'000'000 >();
    test<       10'000'000'000'000 >();
    test<      100'000'000'000'000 >();
    test<     1000'000'000'000'000 >();
    test<   10'000'000'000'000'000 >();
    test<  100'000'000'000'000'000 >();
    test< 1000'000'000'000'000'000 >();
}
100100