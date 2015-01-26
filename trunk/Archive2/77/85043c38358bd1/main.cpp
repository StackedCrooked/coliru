#include <boost/mpl/map.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/string.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/mpl.hpp>

namespace mpl = boost::mpl;
namespace qi = boost::spirit::qi;

struct do_ol   : qi::grammar<const char*> {
    do_ol() : do_ol::base_type(start) {}
    qi::rule<const char*> start;
};
struct do_ul   : qi::grammar<const char*> {
    do_ul() : do_ul::base_type(start) {}
    qi::rule<const char*> start;
};
struct do_para : qi::grammar<const char*> {
    do_para() : do_para::base_type(start) {}
    qi::rule<const char*> start;
};

template <typename T>
struct block_parser_t : qi::symbols<char, T> {

    template <typename Map>
    void add_map() {
        boost::fusion::for_each(Map(), map_adder(*this));
    }

  private:
    struct map_adder {
        map_adder(block_parser_t& r) : _r(r) {}
        block_parser_t& _r;

        template <typename...> struct result { typedef void type; };

        template <typename Pair> void operator()(Pair const&) const { 
            std::cout << "Adding: " << mpl::c_str<typename Pair::first>::value << "\n";
            _r.add(
                mpl::c_str<typename Pair::first>::value,
                typename Pair::second()
            );
        }
    };
};

int main() {
    using blocks = mpl::map<
        mpl::pair<mpl::string<'p'>,  do_para>,
        mpl::pair<mpl::string<'ul'>, do_ul>,
        mpl::pair<mpl::string<'ol'>, do_ol>
    >;

    typedef qi::rule<char const*> R;

    block_parser_t<R> block_parser;
    block_parser.add_map<blocks>();
}
