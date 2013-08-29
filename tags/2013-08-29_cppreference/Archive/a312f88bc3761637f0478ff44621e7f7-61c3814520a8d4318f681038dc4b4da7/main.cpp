#include <iostream>
#include <functional>

std::function<int(int)> f = [](int x){
    auto old_f = f;
    f = [=](int x) {
        return old_f(x) + 1;
    };
    return x;
};


int main()
{
    std::cout << f(0) << std::endl;
    std::cout << f(0) << std::endl;
    std::cout << f(0) << std::endl;
}