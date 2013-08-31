#include <iostream>

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << __FILE__ << ":" << i << ":" << i << std::endl;
    }
}