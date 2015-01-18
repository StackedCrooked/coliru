#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Point {
    float x,y;
    constexpr Point(float x,float y) : x(x), y(y) {}
};

typedef std::vector<Point> data_t;

namespace {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    template <typename OutputIterator>
    struct PreCompile {
        static const qi::rule<char const*, qi::unused_type(OutputIterator& _r1), qi::space_type> precompiled;
    };

    template <typename OI>
    const qi::rule<char const*, qi::unused_type(OI& _r1), qi::space_type> PreCompile<OI>::precompiled =
                *(qi::double_ >> ',' >> qi::double_) [ *qi::_r1 = phx::construct<Point>(qi::_1,qi::_2) ]
                >> &qi::lit('\0');
}

template <typename OI>
static inline void parse_points(char const* szInput, OI out) {
    if (!qi::phrase_parse(
                szInput, 
                std::numeric_limits<char const*>::max(), // just wait for NUL char
                PreCompile<OI>::precompiled(phx::ref(out)), qi::space))
    {
        throw "parse failure";
    }
}

static inline data_t parse_points(char const* szInput) {
    data_t pts;
    parse_points(szInput, back_inserter(pts));
    return pts;
}

int main() {
    std::cout << "elements in sample: " << parse_points( " 10,9 2.5, 3   4 ,150.32    ").size() << "\n";
}
