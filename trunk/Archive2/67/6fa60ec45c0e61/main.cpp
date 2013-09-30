#include <iostream>

std::ostream& operator<<(std::ostream& o, const char* p)
{
    std::cout << "hello ";
    return std::operator<<(o, p);
}

int main()
{
    std::cout << "world";
}
