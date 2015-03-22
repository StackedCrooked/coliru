#include <iostream>
#include <algorithm>

int main()
{
    auto f = [](int i){return i+1;};
    auto g = [](int i){return i-1;};
    auto a = true ? +f : g;
    
    std::cout << a(a(a(39)));
}
