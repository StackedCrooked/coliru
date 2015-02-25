#include <sstream>
#include <iostream>
#include <iomanip>

int main() {
    double value = 1.2345678;
    std::cout << value << std::endl;
    std::ostringstream out;
    out << std::setprecision(2) << value;
    std::cout << out.str() << std::endl;
}
