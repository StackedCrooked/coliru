#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>

namespace qi = boost::spirit::qi;

enum class Category : char {
    Animal='A', Bird='B'
};

enum class Type : char {
    Dog='D', Bird='B'
};

struct Zoo {
    Category    category;
    Type        type;
    std::string name;
    std::string address;
}; 

BOOST_FUSION_ADAPT_STRUCT(Zoo, (Category,category)(Type,type)(std::string,name)(std::string,address))

namespace qi = boost::spirit::qi;
//namespace repo = boost::spirit::repository;
namespace ascii = boost::spirit::ascii;
namespace phx = boost::phoenix;

template <typename Iterator>
struct ZooBuilderGrammar :  qi::grammar<Iterator, ascii::space_type>
{
    ZooBuilderGrammar():ZooBuilderGrammar::base_type(start_)
    {
        using namespace qi;

        category_ = char_("AB") [ _val = phx::static_cast_<Category>(_1) ];
        type_     = char_("DB") [ _val = phx::static_cast_<Type>(_1) ];
        start_    = category_ >> '|' > type_;
    } 
  private:
    qi::rule<Iterator, Category(),        ascii::space_type> category_;
    qi::rule<Iterator, Type(),            ascii::space_type> type_;
    qi::rule<Iterator, ascii::space_type> start_;
};   

/////////////////////////////////////////////////
// For exception output
struct printer {
    typedef boost::spirit::utf8_string string;

    void element(string const& tag, string const& value, int depth) const {
        for (int i = 0; i < (depth*4); ++i) std::cout << ' '; // indent to depth

        std::cout << "tag: " << tag;
        if (value != "") std::cout << ", value: " << value;
        std::cout << std::endl;
    }
};

void print_info(boost::spirit::info const& what) {
    using boost::spirit::basic_info_walker;

    printer pr;
    basic_info_walker<printer> walker(pr, what.tag, 0);
    boost::apply_visitor(walker, what.value);
}
//
/////////////////////////////////////////////////
int main()
{
    typedef std::string::const_iterator It;
    static const ZooBuilderGrammar<It> p;

    for (std::string const str1 : { 
            "A|D|name=tim, address=3 infinite loop",
            "A|C|name=poc, address=5 overflow street" })
    {
        It f(str1.begin()), l(str1.end());

        try {
            bool ok = qi::phrase_parse(f,l,p,ascii::space);

            if (ok)
                std::cout << "Parse success\n";
            else
                std::cout << "Failed to parse '" << str1 << "'\n";

            if (f!=l)
                std::cout << "Remaining unparsed input '" << std::string(f,l) << "'\n";
        } catch(qi::expectation_failure<It> const& x)
        {
            std::cout << "expected: "; print_info(x.what_);
            std::cout << "got: \"" << std::string(x.first, x.last) << '"' << std::endl;
            std::cout << "Expectation failure: " << x.what() << " at '" << std::string(x.first,x.last) << "'\n";
        }
        std::cout << "---------------------------\n";
    }
}
