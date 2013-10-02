#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

////////////////////////////////
// extra facilities
struct get_line_f
{
    template <typename> struct result { typedef size_t type; };
    template <typename It> size_t operator()(It const& pos_iter) const
    {
        return get_line(pos_iter);
    }
};
//
////////////////////////////////

struct Position
{
    Position()
        : line(-1)
    {
    }

    size_t line;
};

struct Number : public Position
{
    Number()
        : Position()
        , value(-1)
        , source()
    {
    }

    unsigned    value;
    std::string source;
};

using namespace boost::spirit;

BOOST_FUSION_ADAPT_STRUCT(Number,
                            (unsigned,    value)
                            (std::string, source)
                            (size_t,      line)
                          )

template <typename Iterator>
struct source_hex : qi::grammar<Iterator, Number(), qi::space_type>
{
    source_hex() : source_hex::base_type(start)
    {
        using qi::eps;
        using qi::hex;
        using qi::lit;
        using qi::raw;
        using qi::_val;
        using qi::_1;
        //using ascii::char_;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;

        start = raw[ qi::no_case["0x"] >> hex [at_c<0>(_val) = _1] ]
                   [ 
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1)) 
                   ]
        ;
    }

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, Number(), qi::space_type> start;
};

#include <iomanip>

int main()
{
    std::string str = "\n\n0x1234";

    typedef line_pos_iterator<std::string::const_iterator> Iterator;
    source_hex<Iterator> g;
    Iterator iter(str.begin());
    Iterator end(str.end());

    Number number;
    bool r = phrase_parse(iter, end, g, qi::space, number);
    if (r && iter == end) {
        std::cout << number.line << ": 0x" << std::setw(8) << std::setfill('0') << std::hex << number.value << " // " << number.source << "\n";
    } else
        std::cout << "Parsing failed\n";
}
