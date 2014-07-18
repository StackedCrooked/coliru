#include <functional>
#include <iostream>
 
int f(int, int) { return 1; }
int g(int, int) { return 2; }
void test(std::function<int(int, int)> const& arg)
{
    std::cout << "test function: ";
    if (arg.target<std::plus<int>>())
        std::cout << "it is plus\n";
    if (arg.target<std::minus<int>>())
        std::cout << "it is minus\n";
 
    int (*const* ptr)(int, int) = arg.target<int(*)(int, int)>();
    if (ptr && *ptr == f)
        std::cout << "it is the function f\n";
    if (ptr && *ptr == g)
        std::cout << "it is the function g\n";
}
 
int main()
{
    test(std::function<int(int, int)>(std::plus<int>()));
    test(std::function<int(int, int)>(std::minus<int>()));
    test(std::function<int(int, int)>(f));
    test(std::function<int(int, int)>(g));
}