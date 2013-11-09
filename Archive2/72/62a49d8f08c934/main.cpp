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

    static const qi::rule<It> start = qi::lazy(phx::ref(allowed)) >> qi::lit("\r\n");

    for (int i=0; i<10; ++i)
    {
        switch(rand()%3)
        {
            case 0: allowed = request; break;
            case 1: allowed = request | response | query; break;
            case 2: allowed = request | response | status | query; break;
        }

        auto ll = [](std::string const& input) { return qi::parse(begin(input), end(input), start); };
        std::cout << "status: " << ll("status\r\n") << "\tresponse: " << ll("response\r\n") << "\trequest: " << ll("request\r\n") << "\n";
    }
}
