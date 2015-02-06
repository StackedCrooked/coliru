#include <boost/lexical_cast.hpp>

#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    const std::string str = "2.01";

    try
    {
        const double b = boost::lexical_cast<double>(str) * 100.0;
        std::cout << "double: " << std::setprecision(18) << std::fixed << b << '\n';
        const int a = boost::lexical_cast<int>(b);
        std::cout << "int: " << a << '\n';
    }
    catch (const std::exception& ex) { std::cerr << ex.what() << '\n'; }
}
