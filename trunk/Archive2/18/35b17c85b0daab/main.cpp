#include <iostream>
#include <sstream>

int main()
{
    std::istringstream in("-111");
    unsigned short x;
    if (in >> x)
        std::cout << x;
    else
        std::cout << "error";
}
