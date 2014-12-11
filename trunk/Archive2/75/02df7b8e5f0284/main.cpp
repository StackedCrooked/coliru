#include <sstream>
#include <iostream>

int main()
{
    std::ostringstream ss;
    ss << "lolol";
    std::stringbuf* buf = ss.rdbuf();
    std::cout << buf;
}
