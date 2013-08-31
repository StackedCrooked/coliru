#include <iostream>
#include <sstream>
#include <string>
#include <vector>


int main()
{
    std::stringstream ss;
    ss << "Hello from GCC " << __VERSION__, "!";
    std::cout << ss.str() << std::endl;
}
