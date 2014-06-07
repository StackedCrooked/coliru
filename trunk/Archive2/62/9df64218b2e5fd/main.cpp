#include <boost/regex.hpp>

int main()
{
    boost::regex e("a.*?b", boost::regex_constants::perl);

    assert(boost::regex_match("acdefghijklmnopqb", e));
}
