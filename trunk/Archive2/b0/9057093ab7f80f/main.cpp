#include <iostream>

int main()
{
    for (auto i = 42u; i >= 0; --i) // ERROR, infinite loop
        std::cout << i;
}
