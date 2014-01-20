#include <iostream>
#include <utility>
#include <functional>

void f(int, int& i, int) { i = 100; }

template<typename F, typename... Ts>
auto prebind(F&& f, Ts&&... args)
{
    return [=] (auto&&... xs) 
    { 
        return f(args..., std::forward<decltype(xs)>(xs)...); 
    };
}

int main(){
    int i = 1337;
    prebind(f, 42, std::ref(i))(0);
    std::cout << i << "\n";
}