template<int N> int test(int = 0); //forward declaration

template<int N> int test(int = sizeof(test<N - 1>()));

#include <iostream>
template<> int test<0>(int)
{
    std::cout << "test<0>" << std::endl;
}
template<int N>
int test(int x) //x is expected to be sizeof(test<N-1>()) which is sizeof(int)
{
    std::cout << "N" << N <<", x = " << x << std::endl;
}
int main()
{
    return sizeof(test<1>()); 
}