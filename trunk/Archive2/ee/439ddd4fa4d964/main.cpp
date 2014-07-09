#include <iostream>

struct T
{
    int y;
    
    T() : y(0)
    {
        int x = 0;
        [&, this](){ x = 1; y = 2; }();
        
        std::cout << x << ' ' << y << '\n';  // 1 2
    }
};

int main()
{
    T t;
}
