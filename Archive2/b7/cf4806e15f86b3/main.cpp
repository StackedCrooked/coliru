#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace phx=boost::phoenix;

#define BOOST_SPIRIT_AUTO(domain_, name, expr)                                  \
    typedef boost::proto::result_of::                                           \
        deep_copy<BOOST_TYPEOF(expr)>::type name##_expr_type;                   \
    BOOST_SPIRIT_ASSERT_MATCH(                                                  \
        boost::spirit::domain_::domain, name##_expr_type);                      \
    BOOST_AUTO(name, boost::proto::deep_copy(expr));                            


namespace ka = boost::spirit::karma;

int main()
{
    typedef std::ostream_iterator<char> iterator_t;

    std::string is1{"123"}, is2{"def"};
    std::vector<std::string> iv1{"123", "456"}, iv2{"123","def"};

    BOOST_SPIRIT_AUTO(karma, num, +ka::char_("0-9"));
    BOOST_SPIRIT_AUTO(karma, nums, num << ka::repeat(phx::size(ka::_val)-1)[ka::lit(";") << num]);
    //auto nums = num%ka::lit(";");

    assert(ka::generate(iterator_t{std::cout}, num << ka::eol, is1) == true);
    assert(ka::generate(iterator_t{std::cout}, num << ka::eol, is2) == false);

    assert(ka::generate(iterator_t{std::cout}, nums << ka::eol, iv1) == true);
    assert(ka::generate(iterator_t{std::cout}, nums << ka::eol, iv2) == false); // Assertion does not fail anymore but the rule is really ugly
}