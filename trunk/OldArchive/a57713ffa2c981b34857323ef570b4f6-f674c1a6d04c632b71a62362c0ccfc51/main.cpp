//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

typedef int*                     InheritedArg;
typedef std::vector<std::string> ExposedAttribute;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, ExposedAttribute(InheritedArg), qi::locals<InheritedArg>, Skipper>
{
    template<typename Cont>
    parser(Cont const& items) : parser::base_type(start)
    {
        using namespace qi;

        for (auto& item : items)
            loopbuilt.add(item, item);

        qqq = loopbuilt // [ _val = _1 ] /*redundant, automatic attribute propagation works*/
            ;

        start %= 
            eps [ _a = _r1 ] >> // copy inherited into qi::locals here
            qqq % ","
            ;

        BOOST_SPIRIT_DEBUG_NODE(start);
        BOOST_SPIRIT_DEBUG_NODE(qqq);
    }

  private:
    qi::symbols<char, std::string> loopbuilt;
    qi::rule<It, std::string(),                  qi::locals<InheritedArg>, Skipper> qqq;
    qi::rule<It, ExposedAttribute(InheritedArg), qi::locals<InheritedArg>, Skipper> start;
};

bool doParse(const std::string& input, const std::vector<std::string> v)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p(v);
    ExposedAttribute data;

    try
    {
        InheritedArg inherited = nullptr;
        bool ok = qi::phrase_parse(f,l,p(inherited),qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: ";
            for (auto& s : data)
                std::cout << "'" << s << "' ";
            std::cout << "\n";
        }
        else std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}

int main()
{
    bool ok = doParse(" def, ghi, zzz ", { "abc", "def", "ghi", "jkl" });
    return ok? 0 : 255;
}
