#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, std::string(), Skipper>
{
    parser() : parser::base_type(start)
    {
        static const std::vector<std::string> not_accepted { "}}", "]]" };

        using namespace qi;
        exclude = exclusions(not_accepted);
        start = *(char_ - exclude);

        BOOST_SPIRIT_DEBUG_NODE(start);
    }

  private:
    qi::rule<It, std::string(), Skipper> start;

    typedef qi::symbols<char, bool> Exclude;
    Exclude exclude;

    template<typename Elements>
    Exclude exclusions(Elements const& elements) {
        Exclude result;

        for(auto& el : elements)
            result.add(el, true);

        return result;
    }
};

int main()
{
    const std::string input = "1 2 3]] 4";
    typedef std::string::const_iterator It;
    It f(begin(input)), l(end(input));

    parser<It> p;
    std::string data;

    bool ok = qi::phrase_parse(f,l,p,qi::space,data);
    if (ok)   
    {
        std::cout << "parse success\n";
        std::cout << "data: " << data << "\n";
    }
    else std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
}
