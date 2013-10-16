//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

typedef std::vector<int64_t> data_t;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, data_t(), Skipper>
{
    parser() : parser::base_type(value_list)
    {
        using namespace qi;

        value_list       = -value_expression % ',';
        value_expression = macro | literal;
        literal          = int_;

        macro            = (_functions > '(' > value_list > ')')
            [ _pass = phx::bind(_1, _2, _val) ];

        _functions.add("fibonacci", &fibonacci);
        _functions.add("range", &range);

        BOOST_SPIRIT_DEBUG_NODES((value_list)(value_expression)(literal)(macro));
    }

  private:
    static bool fibonacci(data_t const& args, data_t& into) {
        // unpack arguments
        if (args.size() != 2)
            return false;
        auto f = args[0], l = args[1];

        // iterate
        uint64_t gen0 = 0, gen1 = 1, next = gen0 + gen1;
        for(auto i = 0u; i <= l; ++i)
        {
            switch(i) {
                case 0: if (i>=f) into.push_back(gen0); break;
                case 1: if (i>=f) into.push_back(gen1); break;
                default:
                    {
                        next = gen0 + gen1;
                        if (i>=f) into.push_back(next); 
                        gen0 = gen1;
                        gen1 = next;
                        break;
                    }
            }
        }

        // done
        return true;
    }

    static bool range(data_t const& args, data_t& into) {
        // unpack arguments
        if (args.size() != 2)
            return false;
        auto f = args[0], l = args[1];

        if (l>f)
            into.reserve(1 + l - f + into.size());
        for(; f<=l; ++f)
            into.push_back(f); // to optimize

        return true;
    }

    qi::rule<It, data_t(),  Skipper> value_list ;
    qi::rule<It, data_t(),  Skipper> value_expression, macro;
    qi::rule<It, int64_t(), Skipper> literal;

    qi::symbols<char, std::function<bool(data_t const& args, data_t& into)> > _functions;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    data_t data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: " << karma::format_delimited(karma::auto_, ' ', data) << "\n";
        }
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

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
    assert(doParse("range(13, 21)"));
}
