#include <boost/spirit/include/qi.hpp>
#include <boost/array.hpp>

// typedef char name_t[5];
typedef boost::array<char, 5> name_t;

struct MyStruct {
    char   code;
    name_t name;
};

using boost::begin;
using boost::end;

namespace boost { namespace spirit { namespace traits {

    template <>
        struct transform_attribute<name_t, std::vector<char>, qi::domain> {
            typedef std::vector<char> type;

            static type pre(name_t&) { return type(); }

            static void post(name_t& val, type const& attr) {
                BOOST_STATIC_ASSERT(sizeof(val)==5);
                assert(attr.size() == sizeof(val));

                std::copy(attr.begin(), attr.end(), begin(val));
            }
            static void fail(name_t&) { }
        };

} } }

namespace qi = boost::spirit::qi;

int main()
{
    std::string const input("123456");

    typedef std::string::const_iterator It;
    It f(input.begin()), l(input.end());

    MyStruct data;
    qi::rule<It, std::vector<char>()> c5 = qi::repeat(5) [ qi::char_ ];
    bool ok = qi::parse(f,l, qi::char_ >> c5, data.code, data.name);

    if (ok)
    {
        std::cout << "Parse success: " << data.code << ", '" << std::string(begin(data.name), end(data.name)) << "'\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
    {
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
