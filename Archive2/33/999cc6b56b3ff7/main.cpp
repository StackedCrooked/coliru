#include <iostream>
#include <tuple>
#include <functional>
 
int main()
{
    auto t1 = std::make_tuple(10, "Test", 3.14);
    std::cout << "The value of t1 is "
              << "(" << std::get<0>(t1) << ", " << std::get<1>(t1)
              << ", " << std::get<2>(t1) << ")\n";
 
    int n = 1;
    auto t2 = std::make_tuple(std::ref(n), n);
    n = 7;
    std::cout << "The value of t2 is "
              << "(" << std::get<0>(t2) << ", " << std::get<1>(t2) << ")\n";
    std::cout << "王军建" << std::endl;
}