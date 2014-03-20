#include <iostream>
#include <bitset>

template<int N,unsigned int P=0> struct Log2 
    { enum { value = Log2<N/2,P+1>::value }; };

template <unsigned p>
struct Log2<0, p> { enum { value = p }; };

template <unsigned p>
struct Log2<1, p> { enum { value = p }; };

int main()
{
    std::bitset<Log2<4>::value> bits;
    std::cout << bits << '\n';
}
