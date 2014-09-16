#include <iostream>
#include <boost/format.hpp>

template<typename... Arguments>
void format_vargs(std::string const& fmt, Arguments&&... args)
{
    boost::format f(fmt);
    std::cout << boost::str(f % args...);
}

int main()
{
    format_vargs("%s %d %d", "Test", 1, 2);
}