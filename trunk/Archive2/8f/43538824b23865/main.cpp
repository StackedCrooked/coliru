#include <sstream>
#include <iostream>

int main()
{
    std::stringstream ss;
    ss << "lolol";
    std::cout << ss.rdbuf()->in_avail();  // 1?!
}
