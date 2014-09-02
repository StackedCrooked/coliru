#include <functional>
#include <iostream>
#include <vector>

int foo(int i) { return i * 2; }

double bar() { return 42.42; }

int bar2(int) { std::cout << "bar2\n"; return 0; }

int main() 
{
    std::vector<std::function<void()>> v; // vectors of functions
    
    v.push_back(std::bind(bar2, 42));
    v.push_back(std::function<double(void)>(bar));
    v.push_back([] { std::cout << "lambda"; });
    v.push_back(std::bind(foo, 42));
    
    for(auto f : v)
        f();
}