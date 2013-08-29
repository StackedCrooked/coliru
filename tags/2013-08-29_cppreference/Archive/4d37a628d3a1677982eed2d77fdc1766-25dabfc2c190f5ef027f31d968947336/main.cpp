#include <iostream>

int main()
{
    std::cout << ">" << (2 >= 0 ? 2 : (-1) * 2 + -3 >= 0 ? -3 : (-1) * -3) << "<" << std::endl;
}
