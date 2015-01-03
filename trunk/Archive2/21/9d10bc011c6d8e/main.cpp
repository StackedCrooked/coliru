#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
 
int main()
{
    double not_a_number = std::log(-1.0);
    if (errno == EDOM) {
        std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
    }
}