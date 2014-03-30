#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = qi::ascii;
namespace phoenix = boost::phoenix;

namespace client
{
    namespace type
    {
        enum code{NUMBER, STRING, BOOL};
    }      

    struct node_type
    {
        type::code type_id; 
        typedef boost::variant<int, std::string> vt_type;
        vt_type value;
    };
}

/*Adapter and grammar:*/
BOOST_FUSION_ADAPT_STRUCT(
        client::node_type,
        (client::type::code, type_id)
        (client::node_type::vt_type, value)
        )

namespace client
{  
    struct or_op
    {
        node_type left, right;
    };
    // Grammar
    template <typename Iterator>
        struct pair_grammar : qi::grammar<
                              Iterator,
                              node_type(), // Grammar generates node_type
                              ascii::space_type
                              >
    {
        pair_grammar() : pair_grammar::base_type(
                expr // main 'rule'
                )
        {
            using qi::lit;
            using qi::lexeme;
            using ascii::char_;
            using qi::int_;
            using ascii::string;
            using namespace qi::labels;

            using phoenix::at_c;
            using phoenix::push_back;

            expr = int_ [at_c<0>(qi::_val) = client::type::NUMBER, at_c<1>(qi::_val) = qi::_1];
        }
        qi::rule<Iterator, node_type(), ascii::space_type> expr;
    };
}

int main()
{
    using namespace client;
    pair_grammar<std::string::const_iterator> grammar;

    std::string const input = "123";
    auto f(input.begin()), l(input.end());

    node_type node;
    bool ok = qi::phrase_parse(f, l, grammar, ascii::space, node);
    assert(ok);
    assert(f == l);
    assert(node.type_id == type::NUMBER);
    assert(node.value == node_type::vt_type(123));
}
