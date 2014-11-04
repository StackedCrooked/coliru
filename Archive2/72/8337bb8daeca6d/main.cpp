#include <iostream>
#include <cmath>

int main()
{
    std::cout << std::trunc(234343.0    ) << '\n'
              << std::trunc(3.41e10     ) << '\n'
              << std::trunc(19.999999999) << '\n'
              << std::trunc(-10.1       ) << '\n'
              << std::trunc(-0.0000001  ) << '\n';
}