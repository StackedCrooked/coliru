#include <iostream>
#include <sstream>

std::stringstream getSs()
{
    std::stringstream ss;
    ss << "abc";
    return ss;
}

int main()
{
    std::stringstream ss;

    ss = getSs();
    std::cout << ss.str();
}
