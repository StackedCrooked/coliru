#include <boost/regex.hpp>

int main()
{
    using namespace boost;

    std::string str("0123456789");
    std::string::const_iterator start = str.begin();
    std::string::const_iterator end = str.end();
    boost::regex re("(?<=(..))", regex_constants::perl);

    regex_constants::match_flag_type flags = match_default;
    boost::smatch match;  

    while (start<end && 
            boost::regex_search(start, end, match, re, flags))
    {
        std::cout << match[1] << "\t";

        start += 1; // NOTE

        //// some smartness that should work for most cases:
        // start = (match.length(0)? match[0] : match.prefix()).first + 1;

        flags |= regex_constants::match_prev_avail;
        flags |= regex_constants::match_not_bob;

        std::cout << "at '" << std::string(start,end) << "'\n";
    }
}

