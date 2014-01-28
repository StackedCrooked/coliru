#include <boost/regex.hpp>
using boost::regex;

int main()
{
    std::string const input("@anything but &at; followed of the string .PV@");

    boost::smatch matches;
    if(regex_search(input, matches, regex("@(.*?)\\.PV@")))
        std::cout << "Parse success, match string: '" << matches[1] << "'\n";
}
