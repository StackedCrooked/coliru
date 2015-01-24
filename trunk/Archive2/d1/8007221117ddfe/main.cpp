#include <iostream>

int main()
{
    auto lambda = []
    {
        return &__func__;
    };
    
    auto lambda2 = []
    {
        return &__func__;
    };
    
    std::cout << lambda() << ' '
              << lambda2();
}
