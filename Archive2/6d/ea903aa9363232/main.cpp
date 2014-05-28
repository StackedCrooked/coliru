#include <iostream>

int main()
{
    auto factorial = [](int n)
    {
        static auto self = [](auto&& factorial, int n) -> int
        {
            return n < 2 ? 1 : n * factorial(factorial, n - 1);
        };
        return self(self, n);
    };
    
    std::cout << factorial(5) << std::endl;
}
