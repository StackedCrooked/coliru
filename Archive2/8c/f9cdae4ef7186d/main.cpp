#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

void
doTest(
    const std::string &str)
{
    long double val1 = std::strtold(str.c_str(), nullptr);
    std::cout << str << " - std::isinf from strtod: " << std::boolalpha <<
        std::isinf(val1) << '\n';

    std::stringstream sstream(str.c_str());
    double val2;
    sstream >> val2;
    
    std::cout << val2 << std::endl ;
    
    std::cout << str << " - std::isinf from stringstream: " <<
        std::boolalpha << std::isinf(val2) << '\n';

    std::cout << val1 << " vs " << val2 << '\n';

    std::cout << std::endl;
}

int
main()
{
    doTest("INFINITY");
    doTest("+INF");

    return (0);
}