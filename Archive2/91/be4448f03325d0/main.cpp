#include <iostream>
#include <cmath>

int main()
{
    std::cout << (long long)std::trunc(234343.0    ) << '\n'
              << (long long)std::trunc(3.41e10     ) << '\n'
              << (long long)std::trunc(19.999999999) << '\n'
              << (long long)std::trunc(-10.1       ) << '\n'
              << (long long)std::trunc(-0.0000001  ) << '\n';
}