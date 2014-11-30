#include <boost/regex.hpp>
#include <vector>
#include <iostream>

int main()
{
    std::string line("one;two#three//four five\r\n"
            "six");

    boost::regex re("[^a-zA-Z0-9]");
    boost::sregex_token_iterator i(line.begin(), line.end(), re, -1), j;
    std::vector<std::string> split_(i, j);

    for(auto const& s : split_)
        std::cout << s << "\n";
}
