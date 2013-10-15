#define BOOST_RESULT_OF_USE_DECLTYPE // needed for gcc 4.7, not clang++
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <functional>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

// okay, so you want position reporting (actually unrelated):
#include <boost/spirit/include/support_line_pos_iterator.hpp>
using It = boost::spirit::line_pos_iterator<std::string::const_iterator>;

namespace { 
    struct get_line_f {
        template <typename> struct result { typedef size_t type; };
        template <typename It> size_t operator()(It const& pos_iter) const {
            return get_line(pos_iter);
        }
    };
}

static const phx::function<get_line_f> get_line_;

// the exposed attribute for the parser:
using Numbers    = std::set<double>;

// the callback signature for our warning; you could make it more like
// `on_error` so it takes the iterators directly, but again, I'm doing the
// simple thing for the dmeo
using Callback = std::function<bool(std::string const& source, size_t line)>;

template <typename It>
    struct parser : qi::grammar<It, Numbers()>
{
    parser(Callback warning) 
        : parser::base_type(start),
          warning(warning)
    {
        using namespace qi;
        auto check_unique = phx::end(_r1) == phx::find(_r1, _val);

        word   = raw [ double_ [ _val = _1 ] ] 
                    [ 
                      _pass = check_unique || phx::bind(warning, 
                                phx::construct<std::string>(phx::begin(_1), phx::end(_1)), 
                                get_line_(phx::begin(_1)))
                    ]
               ;

        start = -word(_val) % +space >> eoi;
    }

  private:
    Callback warning;
    qi::rule<It, double(Numbers const&)> word;
    qi::rule<It, Numbers()> start;
};

int main(int argc, const char *argv[])
{
    // parse command line arguments
    const auto flags          = std::set<std::string> { argv+1, argv+argc };
    const bool fatal_warnings = end(flags) != flags.find("-Werror");

    // test input
    const std::string input("2.4 240000e-5");

    // warning handler
    auto warning_handler = [&](std::string const& source, size_t line) { 
        std::cerr << (fatal_warnings?"Error":"Warning") 
                  << ": Near-identical entry '" << source << "' at L:" << line << "\n"; 
        return !fatal_warnings;
    };

    // do the parse
    It f(begin(input)), l(end(input));
    bool ok = qi::parse(f, l, parser<It>(warning_handler));

    // report results
    if (ok)   std::cout << "parse success\n";
    else      std::cerr << "parse failed\n";
    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";

    // exit code
    return ok? 0 : 255;
}

