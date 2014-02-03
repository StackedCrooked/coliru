#include <iostream>
int main()
{
        std::cout << "showpos: " << std::showpos << 42 << ' ' << 3.14 << ' ' << 0 << '\n'
                  << "noshowpos: " << std::noshowpos << 42 << ' ' << 3.14 << ' ' << 0 << '\n';
}