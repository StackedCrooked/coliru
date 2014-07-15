#include <boost/regex.hpp>

int main()
{
    using namespace boost;

    std::string str("0123456789");
    std::string::const_iterator start = str.begin();
    std::string::const_iterator end = str.end();
    boost::regex re("(?<=(..))", regex_constants::perl);

    boost::smatch match;  

    while (boost::regex_search(start, end, match, re))
    {
        std::cout << match[1] << "\n";
        start = match[1].first+1; // NOTE
    }
}