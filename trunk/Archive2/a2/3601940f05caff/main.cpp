#include <iostream>
#include <utility>
#include <functional>

void f(int, int& i, int) { i = 100; }

int g(int a, int b, int c, int d) { return a + b + c + d; }

template<typename F, typename... Ts>
auto prebind(F&& f, Ts&&... args)
{
    return [=] (auto&&... xs) 
    { 
        return f(args..., std::forward<decltype(xs)>(xs)...); 
    };
}

int main()
{
    int i = 1337;
    prebind(f, 42, std::ref(i))(0);
    std::cout << i << "\n";
    
    auto b = prebind(g, 1);
    std::cout << b(3, 8, 13);
}