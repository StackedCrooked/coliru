// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

template <typename T> struct ChainLink;

template <typename T>
class SimpleLinkList {
  public:
    void push_back(T const& v) { /* todo */ _for_debug.push_back(v); }
    
    std::list<int> _for_debug;
    friend std::ostream& operator<<(std::ostream& os, SimpleLinkList const& list) {
        os << "["; std::copy(list._for_debug.begin(), list._for_debug.end(), std::ostream_iterator<T>(os, " ")); return os << "]";
    }
  private:
    ChainLink<T>* head;
};

namespace boost { namespace spirit { namespace traits {
    template <typename T>
        struct container_value<SimpleLinkList<T>, void> {
            typedef T type;
        };

    template <typename T>
        struct push_back_container<SimpleLinkList<T>, T, void> {
            static bool call(SimpleLinkList<T>& c, T const& val) {
                c.push_back(val);
                return true;
            }
        };
}}}

struct AbstractDataType
{
    int number;
    SimpleLinkList<int> list1, list2;
};

BOOST_FUSION_ADAPT_STRUCT(AbstractDataType, (int, number)(SimpleLinkList<int>, list1)(SimpleLinkList<int>, list2))

template<typename Iterator>
struct parser_expression : qi::grammar<Iterator, AbstractDataType(), qi::space_type> 
{
    parser_expression() : parser_expression::base_type(start) 
    {
        list  = '[' >> -(qi::int_ % ',') >> ']';
        start = qi::int_ >> list >> -list >> '=';

        BOOST_SPIRIT_DEBUG_NODES((list)(start))
    }

    qi::rule<Iterator, AbstractDataType(),    qi::space_type> start;
    qi::rule<Iterator, SimpleLinkList<int>(), qi::space_type> list;
};

void test(const std::string input)
{
    static const parser_expression<std::string::const_iterator> p;

    AbstractDataType parsed;
    auto f(input.begin()), l(input.end());
    bool ok = qi::phrase_parse(f, l, p, qi::space, parsed);

    if (ok)
        std::cout << "Result: " << parsed.number << " " << parsed.list1 << parsed.list2 << "\n";
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Unparsed: '" << std::string(f,l) << "'\n";
}

int main()
{
    test("1 [2, 3, 4] [5, 6] =");
    test("2 []        [6, 7] =");
    test("3 [4, 5, 6] [    ] =");
    test("4 [5, 6, 7]        =");
}
