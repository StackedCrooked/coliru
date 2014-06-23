#include <iostream>
#include <sstream>

int main()
{
    unsigned x;
    if (!(std::istringstream("-1") >> x))
        std::cout << "fail\n";
}
