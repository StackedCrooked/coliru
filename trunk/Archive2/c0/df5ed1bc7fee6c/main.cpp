#define BOOST_SPIRIT_DEBUG
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace qi = boost::spirit::qi;

//////////////////////////////////////////
// Select workaround to demonstrate
// #define KEEP_STRING_WORKAROUND
// #define DUMMY_WORKAROUND
#define NO_ADAPT_WORKAROUND
//////////////////////////////////////////

#if defined(KEEP_STRING_WORKAROUND)
    struct identifier
    {
        std::string    name;
    };

    BOOST_FUSION_ADAPT_STRUCT(
        identifier,
        (std::string,    name)
    )
#elif defined(DUMMY_WORKAROUND)
    struct identifier
    {
        std::string    name;
        qi::unused_type dummy;
    };

    BOOST_FUSION_ADAPT_STRUCT(
        identifier,
        (std::string,    name)
        (qi::unused_type, dummy)
    )
#elif defined(NO_ADAPT_WORKAROUND)
    struct identifier
    {
        std::string name;
        
        identifier() = default;

        explicit identifier(std::string name) 
            : name(std::move(name))
        {}
    };
#endif

struct problem
{
    identifier _1;
    identifier _2;
    identifier _3;
};

BOOST_FUSION_ADAPT_STRUCT(
    problem,
    (identifier, _1)
    (identifier, _2)
    (identifier, _3)
)

//////////////////////////////////////////
// For BOOST_SPIRIT_DEBUG only:
static inline std::ostream& operator<<(std::ostream& os, identifier const& id) {
    return os << id.name;
}
//////////////////////////////////////////

int main()
{
    using namespace qi;
    typedef std::string::const_iterator It;
#if defined(KEEP_STRING_WORKAROUND)
    rule<It, std::string()> gr_identifier = 
        (alpha | '_') >> *(alnum | '_');
#elif defined(DUMMY_WORKAROUND)
    rule<It, identifier()> gr_identifier = 
        (alpha | '_') >> *(alnum | '_') >> attr(42);   // that's hacky
#elif defined(NO_ADAPT_WORKAROUND)
    rule<It, identifier()> gr_identifier = 
        as_string [ (alpha | '_') >> *(alnum | '_') ]; // cleaner... but no fusion
#endif

    rule<It, problem(), qi::space_type> gr_problem = 
           gr_identifier
        >> gr_identifier
        >> ('(' > gr_identifier > ')') // TODO expectations
        ;

    std::string input = "foo goo(hoo)";

    BOOST_SPIRIT_DEBUG_NODES((gr_problem)(gr_identifier));

    It f(begin(input)), l(end(input));
    bool dummy = phrase_parse(f, l, gr_problem, qi::space);

    return dummy? 0 : 255;
}
