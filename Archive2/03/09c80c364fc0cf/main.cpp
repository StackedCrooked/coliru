#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>
 
int main() 
{
    std::vector<int>v = {0,1,2,3,4,5,6};
    auto f_lambda = [&v](int i) { return v[i];};
    std::function<const int&(int)> f = f_lambda; 
    auto g_lambda = [&v](int i) -> const int& { return v[i];};
    std::function<const int&(int)> g = g_lambda;
 
    std::cout << std::is_same<decltype(f_lambda(3)), int>::value << "\n";
    std::cout << std::is_same<decltype(f_lambda(3)), const int&>::value << "\n";
    std::cout << std::is_same<decltype(g_lambda(3)), int>::value << "\n";
    std::cout << std::is_same<decltype(g_lambda(3)), const int&>::value << "\n";
    std::cout << f(3) << ' ' << g(3) << std::endl;
    return 0;
}