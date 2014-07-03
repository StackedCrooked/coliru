#include <iostream>


template<typename T>
std::ostream& operator<<(std::ostream& os, T t)
{
    return os << t;
}


int main()
{
    const char* c = nullptr;
    using std::operator<<; // disambiguate
    std::cout << c << std::endl;
}
