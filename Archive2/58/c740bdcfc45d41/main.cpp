#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Point {
    float x,y;
    constexpr Point(float x,float y) : x(x), y(y) {}
};

typedef std::vector<Point> data_t;

template <typename Out>
static inline void parse_points(char const* szInput, Out out) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    static const qi::rule<char const*, qi::unused_type(Out& _r1), qi::space_type> precompiled =
            *(qi::double_ > ',' > qi::double_) [ *qi::_r1 = phx::construct<Point>(qi::_1,qi::_2) ]
            > &qi::lit('\0');

    // fake end iterator; we'll watch for NUL char
    static constexpr char const* adnauseam = std::numeric_limits<char const*>::max(); 

    if (!qi::phrase_parse(szInput, adnauseam, precompiled(phx::ref(out)), qi::space))
        throw "parse failure";
}

int main(){
    char const* const sample = " 10,9 2.5, 3   4 ,150.32    ";

    data_t data;
    data.reserve(100); // optional; may reduce reallocs

    parse_points(sample, back_inserter(data));
    parse_points(sample, back_inserter(data));
    parse_points(sample, back_inserter(data));

    std::cout << "data.size(): " << data.size() << " elements\n";
}
