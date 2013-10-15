#define BOOST_RESULT_OF_USE_DECLTYPE // needed for gcc 4.7, not clang++
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <functional>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

// okay, so you want position reporting (actually unrelated):
using It = boost::spirit::line_pos_iterator<std::string::const_iterator>;

// AST type that represents a Word 'token' (with source location information)
struct Word 
{ 
    It begin, end; 
    explicit Word(boost::iterator_range<It> const& range = {})
        : begin(range.begin()), end(range.end()) {}

    // not optimizing, demo only, your AST will be smarter :)
    std::string str() const { return std::string(begin, end); }
    bool operator< (const Word& other) const { return str() <  other.str(); }
    bool operator==(const Word& other) const { return str() == other.str(); }
    bool operator!=(const Word& other) const { return str() != other.str(); }
};

// the exposed attribute for the parser:
using Words    = std::set<Word>;

// the callback signature for our warning; you could make it more like
// `on_error` so it takes the iterators directly, but again, I'm doing the
// simple thing for the dmeo
using Callback = std::function<bool(Word const& s)>;

template <typename It>
    struct parser : qi::grammar<It, Words()>
{
    parser(Callback warning) 
        : parser::base_type(start),
          warning(warning)
    {
        using namespace qi;
        auto check_unique = phx::end(_val) == phx::find(_val, _1);

        word   = 
               raw [+graph] [ _val = phx::construct<Word>(_1) ]
               ;

        start %= 
               - word       [ _pass = check_unique || phx::bind(warning, _1) ]
               % +space
               >> eoi
               ;
    }

  private:
    Callback warning;
    qi::rule<It, Word()>  word;
    qi::rule<It, Words()> start;
};

int main(int argc, const char *argv[])
{
    // parse command line arguments
    const auto flags          = std::set<std::string> { argv+1, argv+argc };
    const bool fatal_warnings = end(flags) != flags.find("-Werror");

    // test input
    const std::string input("the lazy \n\n\ncow \n\njumped over the \nthe lazy\nmoon\n");

    // warning handler
    auto warning_handler = [&](Word const& w) { 
        std::cerr << (fatal_warnings?"Error":"Warning") 
                  << ": Duplicate entry '" << w.str() << "' at L:" << get_line(w.begin) << "\n"; 
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
