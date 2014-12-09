#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>


int main()
{
    std::string str1("3fb999999999999a"); //  0.1
    std::string str2("bfb999999999999a"); // -0.1


    // ******************************
    // UNION
    // ******************************
    union uint64double
    {
        unsigned long long i;
        double    d;
    };

    uint64double val1;
    val1.i = std::stoll(str1, nullptr, 16);

    uint64double val2;
    val2.i = std::stoll(str2, nullptr, 16);     // This throws std::out_of_range exception

    const int w = 18;

    std::cout << "USING UNION" << std::endl;
    std::cout << std::setw(w) << "HEX" << std::setw(w) << "DOUBLE" << std::endl;
    std::cout << std::setw(w) << str1 << std::setw(w) << val1.d << std::endl;
    std::cout << std::setw(w) << str2 << std::setw(w) << val2.d << std::endl;

    std::cout << std::endl;


    // ******************************
    // STRINGSTREAM
    // ******************************
    unsigned long long i1;
    std::stringstream ss;
    ss << std::hex << str1;
    ss >> i1;
    double d1(reinterpret_cast<double&>(i1));

    unsigned long long i2;
    ss.clear();
    ss << std::hex << str2;
    ss >> i2;
    double d2(reinterpret_cast<double&>(i2));

    std::cout << "USING STRINGSTREAM" << std::endl;
    std::cout << std::setw(w) << "HEX" << std::setw(w) << "DOUBLE" << std::endl;
    std::cout << std::setw(w) << str1 << std::setw(w) << d1 << std::endl;
    std::cout << std::setw(w) << str2 << std::setw(w) << d2 << std::endl;

    std::cout << std::endl;

    return 0;
}