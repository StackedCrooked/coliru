#include <boost/xpressive/xpressive_static.hpp>
#include <iostream>
namespace xp = boost::xpressive;

int main()
{
    std::string const tests[] = {
        "SomeString #222",
        "SomeString #1",
        "SomeString #42",
        "SomeString #-1"
    };

    for(auto& input : tests)
    {
        static xp::sregex rex = (xp::s1= -*xp::_) >> '#' >> (xp::s2= !xp::as_xpr('-') >> +xp::_d);

        xp::smatch what;

        if(xp::regex_match(input, what, rex))
        {
            std::cout << "Input '" << what[0] << " -> " << what[2] << '\n';
        }
    }
}
