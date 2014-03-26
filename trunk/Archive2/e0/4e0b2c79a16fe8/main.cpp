#include <iostream>
#include <string>
#include <boost/regex.hpp>

struct formatter
{
    std::string operator()(boost::smatch const& in) const
    {
//        std::cout << "'" << in.str() << "'" <<  '\n';
        return std::to_string(std::stoi(in.str()) + 1);
    }
};

int main()
{
    boost::regex re(R"(\d+)");
    std::cout << boost::regex_replace(std::string("my values are 9, 19"), re, formatter()) << '\n';
}
