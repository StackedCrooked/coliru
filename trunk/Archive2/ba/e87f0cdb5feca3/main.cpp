#include <boost/regex.hpp>

int main()
{
    using namespace boost;

    std::string str("0123456789");
    std::string::const_iterator start = str.begin();
    std::string::const_iterator end = str.end();
    boost::regex re("..", regex_constants::perl);

    regex_constants::match_flag_type flags = match_default;
    boost::smatch match;  

    while (boost::regex_search( start, end, match, re, flags))
    {
        std::cout << std::string(match[0].first, match[0].second ) << "\n";
        start = match[0].first+1;
    }
}
