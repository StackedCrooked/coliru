#include <iostream>
#include <sstream>
#include <iomanip>

int main (int argc, char ** argv) {
    std::stringstream s;
    double d = 3.6;
    s << std::fixed << std::setprecision(3) << d;
    std::string res = s.str();
    std::cout << res;
}