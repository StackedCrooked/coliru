#include <random>
#include <iostream>
#include <functional>
 
 
int g(int n1, int n2)
{
    return n1 - n2;
}
 
int main()
{
    using namespace std::placeholders;  // for _1, _2, _3...

    auto f3 = std::bind(g, _3, _1);

    std::cout << f3(20,2) << '\n';
}