#include <string>
#include <iostream>
#include <cstring>
#include <stdexcept>

void find_coordinates(const std::string& str, int& x, int& y)
{
    if (sscanf(str.c_str(), "( %d , %d )", &x, &y) != 2)
       throw std::runtime_error("Parsing failed");
}

int main()
{
    int x, y;
    find_coordinates("( 5 , 10 )", x, y);
    std::cout << x << ' ' << y << '\n';
}