#include <iostream>
#include <vector>
#include <functional>

int main() 
{
    std::vector<int>v = {0,1,2,3,4,5,6};
    std::function<const int&(int)> f = [&v](int i) { return v[i];}; 
    std::function<const int&(int)> g = [&v](int i) -> const int& { return v[i];};

    std::cout << f(3) << ' ' << g(3) << std::endl;
    return 0;
}