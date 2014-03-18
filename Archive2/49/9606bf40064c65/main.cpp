#include <iostream>
#include <bitset>
#include <functional>
 
int main()
{
    std::bitset<4> b1(1);
    std::bitset<4> b2(2);
    std::bitset<4> b3(b2);
 
    std::hash<std::bitset<4>> hash_fn;
 
    size_t h1 = hash_fn(b1);
    size_t h2 = hash_fn(b2);
    size_t h3 = hash_fn(b3);
 
    std::cout << h1 << '\n';
    std::cout << h2 << '\n';
    std::cout << h3 << '\n';
}