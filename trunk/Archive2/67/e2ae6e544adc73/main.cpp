#include <sstream>
#include <iostream>

int main()
{
    {
        std::ostringstream ss;
        ss << "lolol";
        std::cout << ss.rdbuf() << '\n';
    }
    {
        std::stringstream ss;
        ss << "brap brap";
        std::cout << ss.rdbuf() << '\n';
    }
}
