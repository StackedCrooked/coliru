#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phx   = boost::phoenix;

namespace hdb
{
    typedef std::string Header;
    template <typename T> struct Key
    {
        Header header;
        T      value;
    };

    struct AST
    {
        std::vector<Key<std::string> > string_keys;
        std::vector<Key<double> >      value_keys;
    };
}

BOOST_FUSION_ADAPT_STRUCT(
    hdb::Key<std::string>,
    (hdb::Header, header)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    hdb::Key<double>,
    (hdb::Header, header)
    (double, value)
)

namespace boost { namespace spirit { namespace traits {

template<>
    struct is_container<hdb::AST, void> : mpl::true_ { };

template<>
    struct container_value<hdb::AST, void> {
         typedef boost::variant< hdb::Key<std::string> ,hdb::Key<double> > type;
    };

template <>
    struct push_back_container<hdb::AST, hdb::Key<std::string>, void> {
        static bool call(hdb::AST& f, const hdb::Key<std::string>& val) {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            f.string_keys.push_back(val);
            return true;
        }
    };
template <>
    struct push_back_container<hdb::AST, hdb::Key<double>, void> {
        static bool call(hdb::AST& f, const hdb::Key<double>& val) {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            f.value_keys.push_back(val);
            return true;
        }
    };

} } }

template <typename Iterator>
struct hdb_grammar : qi::grammar<Iterator, hdb::AST(), ascii::space_type>
{

    hdb_grammar() : hdb_grammar::base_type(ast)
    {
        using ascii::char_;

        ast        = (value_key|string_key);
        header     = qi::lexeme['[' >> +~char_("[]") >> ']'];
        string_key = header >> +~char_("[]");
        value_key  = header >> qi::double_;

        BOOST_SPIRIT_DEBUG_NODES((header)(string_key)(value_key))
    }

    qi::rule<Iterator, hdb::AST(),              ascii::space_type> ast;
    qi::rule<Iterator, hdb::Header(),           ascii::space_type> header;
    qi::rule<Iterator, hdb::Key<double>(),      ascii::space_type> value_key;
    qi::rule<Iterator, hdb::Key<std::string>(), ascii::space_type> string_key;
};

int main()
{
    const std::string contents = 
        "[key 1] value 1\n"
        "[key 2] 2.78\n";

    typedef hdb_grammar<std::string::const_iterator> grammar;
    grammar g; // Our grammar
    hdb::AST ast; // Our tree

    using boost::spirit::ascii::space;
    std::string::const_iterator begin = contents.begin(), end = contents.end();
    bool success = qi::phrase_parse(begin, end, *g, space, ast); // Only fills "key 1" & not "key 2"

    for (auto& e : ast.string_keys) std::cout << "string_key:\t" << e.header << ", " << e.value << "\n";
    for (auto& e : ast.value_keys)  std::cout << "value_key:\t"  << e.header << ", " << e.value << "\n";
}