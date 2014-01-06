#include <algorithm>
#include <iostream>
#include <functional>

int main()
{
    std::vector<int> x = {1, 2, 3};
    auto y = x;
    std::transform(x.begin(), x.end(), x.begin(), std::bind1st(std::plus<int>(), 7));
    for(auto&& item : y) item+=7;
    
    for(auto&& item : x) std::cout << item << '\n';
    for(auto&& item : y) std::cout << item << '\n';
}