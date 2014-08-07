#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>

enum class Category : char { Animal='A', Bird='B' };
enum class Type     : char { Dog='D',    Bird='B' };

struct Zoo {
    Category category;
    Type     type;
}; 

BOOST_FUSION_ADAPT_STRUCT(Zoo, (Category,category)(Type,type))

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct ZooBuilderGrammar :  qi::grammar<Iterator, Zoo(), ascii::space_type>
{
    ZooBuilderGrammar():ZooBuilderGrammar::base_type(start_)
    {
        start_ = category_ > '|' > type_;
    } 
  private:
    struct Category_ : qi::symbols<char,Category> {
        Category_() {
            this->add("A", Category::Animal)("B", Category::Bird);
        }
    } category_;
    struct Type_ : qi::symbols<char,Type> {
        Type_() {
            this->add("D", Type::Dog)("B", Type::Bird);
        }
    } type_;
    qi::rule<Iterator, Zoo(), ascii::space_type> start_;
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
            Zoo zoo;
            bool ok = qi::phrase_parse(f,l,p,ascii::space,zoo);

            if (ok)
                std::cout << "Parse success: [" << static_cast<char>(zoo.category) << ", " << static_cast<char>(zoo.type) << "]\n";
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
