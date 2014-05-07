#include <iostream>

int main()
{
    auto add = [](auto x)
    {
        return [=](auto y)
        { 
            std::cout << "x = " << x << '\n';
            std::cout << "y = " << y << '\n';
            auto result = x + y;
            std::cout << "result = " << result << '\n';
            return result;
        };
    };
    
    add(5)(4); // 9
}
