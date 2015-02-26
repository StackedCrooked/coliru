#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


std::string toHexBuffer(std::string const & s)
{
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::uppercase << std::setw(2);
    for (auto& c : s)
        os << int(c) << " ";

    return os.str();
}


int main()
{
    std::string const s("Saperlipopette !");
    std::cout << s << std::endl;
    std::cout << toHexBuffer(s) << std::endl;
}
