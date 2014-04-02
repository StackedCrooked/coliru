#include <iostream>
#include <vector>
#include <iterator>
#include <typeinfo>
 
int main() 
{
    int v[3] = { 3, 1, 4 };
    auto vi = std::begin(v);
    std::cout << *vi << '\n'; 
    std::cout <<typeid(typeid(v).name()).name() << '\n';
    int a[] = { -5, 10, 15 };
    auto ai = std::begin(a);
    std::cout << *ai << '\n';
}