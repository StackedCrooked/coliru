
#include <iostream>
#include <type_traits>

template<int N>
//struct X { int c[N/4]; char a[N/2]; int b[N/3] ; };
struct X { char a[N]; };

template<int size>
void experiment()
{  
    alignas(X<size>) char s[sizeof(X<size>)];
    alignas(8) char s8[sizeof(X<size>)];
    alignas(16) char s12[sizeof(X<size>)];
    std::cout << size << " => " << sizeof(s8) << " # "<<alignof(decltype(s8)) << " : " << ((unsigned long long)(void*)(s8)) % 8;
    std::cout << std::endl;
}

int main()
{
    experiment<4>();
    experiment<6>();
    experiment<8>();
    experiment<10>();
    experiment<12>();
    experiment<14>();
    experiment<16>();
    experiment<18>();
    experiment<32>();
    experiment<64>();
}