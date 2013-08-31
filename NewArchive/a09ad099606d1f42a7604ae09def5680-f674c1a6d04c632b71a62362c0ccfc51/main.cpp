#include <iostream>

int main()
{
    auto f = []( long long n ) { return n & 0x1000000000000000 ? n | 0x1000000000000000 : -(n & ~0x1000000000000000); };
    std::cout << f(f(42)) << std::endl;
}