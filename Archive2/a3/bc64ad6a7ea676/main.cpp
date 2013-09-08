#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>

int main()
{
    std::string name;
    std::cout << "\n Enter your first name\n";
    std::cin >> name;

    boost::replace_all(name, "a", "ka");
    boost::replace_all(name, "b", "zu");
    std::cout << name << '\n';
}
