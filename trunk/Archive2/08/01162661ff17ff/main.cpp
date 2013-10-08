#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <functional>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

template <typename It>
    struct parser : qi::grammar<It>
{
    parser(std::function<bool(std::string const& s)> callback) 
        : parser::base_type(start),
          callback(callback)
    {
        using namespace qi;

        start %= 
            as_string[+graph] 
                [ _pass = phx::bind(callback, _1) ]
            % +space
            ;

        BOOST_SPIRIT_DEBUG_NODES((start));
    }

  private:
    std::function<bool(std::string const& s)> callback;
    qi::rule<It> start;
};

int main()
{
    typedef std::string::const_iterator It;

    const std::string input("1 2 abort 4");
    It f(begin(input)), l(end(input));

    auto warning_handler = [](std::string const& s) { 
        std::cerr << "Warning: word parsed: '" << s << "'\n"; 
        return s!="abort"; 
    };
    parser<It> p(warning_handler);

    bool ok = qi::parse(f,l,p);

    if (ok)   std::cout << "parse success\n";
    else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";
    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";

    return ok? 0 : 255;
}
