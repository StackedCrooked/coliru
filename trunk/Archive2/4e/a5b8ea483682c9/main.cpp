#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;

struct ast;

//typedef boost::make_recursive_variant<boost::recursive_wrapper<ast> >::type node;
typedef boost::variant<boost::recursive_wrapper<ast> > node;

struct ast {
    std::vector<int> value;
    std::vector<node> children;
};

BOOST_FUSION_ADAPT_STRUCT(ast,
    (std::vector<int>,value)
    (std::vector<node>,children)
)

template <typename It, typename Skipper = qi::space_type>
struct grammar : qi::grammar<It, ast(), Skipper>
{
    grammar() : grammar::base_type(start) {
        using namespace qi;
        start = '{' >> -(int_ % ',') >> ';' >> -(start % ',') >> '}';
        //BOOST_SPIRIT_DEBUG_NODES((start));
    }
  private:
    qi::rule<It, ast(), Skipper> start;
};

// for output:
static inline std::ostream& operator<<(std::ostream& os, ast const& v) {
    using namespace karma;
    rule<boost::spirit::ostream_iterator, ast()> r;
    r = '{' << -(int_ % ',') << ';' << -((r|eps) % ',')  << '}';
    return os << format(r, v);
}

template <typename It> void parse(It f, It l, ast& into) 
{
    static grammar<It> g;
    bool ok = qi::phrase_parse(f,l,g,qi::space,into);

    if (!ok || (f!=l)) {
        std::cout << "Parse failure\n";
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
        exit(255);
    }
}

int main() {
    ast merged;
    for(std::string const& input : {
            "{1 ,2 ,3 ;{4 ;{9 , 8 ;}},{5 ,6 ;}}",
            "{10,20,30;{40;{90, 80;}},{50,60;}}",
            })
    {
        parse(input.begin(), input.end(), merged);
        std::cout << "merged + " << input << " --> " << merged << "\n";
    }
}
