#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

int main()
{
    using std::string;
    typedef string::const_iterator It;
    qi::rule<It> 
        request  = "request",
        response = "response",
        status   = "status",
        query    = "query";

    for (int i=0; i<10; ++i)
    {
        std::function<bool(string)> test;
        switch(rand()%3)
        {
            case 0: test = [&](std::string const& input) { return qi::parse(begin(input), end(input), request); }; break;
            case 1: test = [&](std::string const& input) { return qi::parse(begin(input), end(input), request | response | query); }; break;
            case 2: test = [&](std::string const& input) { return qi::parse(begin(input), end(input), request | response | status | query); }; break;
        }

        std::cout << "status: "    << test("status\r\n")   << "\t"
                  << "response: "  << test("response\r\n") << "\t"
                  << "request:  "  << test("request\r\n")  << "\n";
    }
}
