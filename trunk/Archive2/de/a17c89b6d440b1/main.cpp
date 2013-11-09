#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

int main()
{
    typedef std::string::const_iterator It;
    qi::rule<It> 
        request  = "request",
        response = "response",
        status   = "status",
        query    = "query",
        // 
        allowed;

    static qi::rule<It> const start = qi::lazy(phx::ref(allowed)) >> qi::lit("\r\n");
    static const auto test = [](std::string const& input) { return qi::parse(begin(input), end(input), start); };

    for (int i=0; i<10; ++i)
    {
        switch(rand()%3)
        {
            case 0: allowed = request; break;
            case 1: allowed = request | response | query; break;
            case 2: allowed = request | response | status | query; break;
        }

        std::cout << "status: "      << test("status\r\n")
                  << "\tresponse: "  << test("response\r\n")
                  << "\trequest:  "  << test("request\r\n")  << "\n";
    }
}
