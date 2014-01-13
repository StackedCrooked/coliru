#include <iostream>
#include <sstream>

int main()
{
    std::istringstream iss("   -89");
    iss >> std::ws;
    std::cout << (char)iss.peek();
}
    