#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Point {
    float x,y;
    constexpr Point(float x,float y) : x(x), y(y) {}
};

template <typename OI>
static inline void parse_points(OI out, char const* it, char const* last = std::numeric_limits<char const*>::max()) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    bool ok = qi::phrase_parse(it, last,
            *(qi::double_ >> ',' >> qi::double_) [ *phx::ref(out) = phx::construct<Point>(qi::_1, qi::_2) ],
            qi::space);

    if (!ok || !(it == last || *it == '\0')) {
        throw it; // TODO proper error reporting?
    }
}

int main(){
    char const* const sample = " 10,9 2.5, 3   4 ,150.32    ";

    std::vector<Point> data;
    data.reserve(100); // optional; may reduce reallocs

    try {
        parse_points(sample, back_inserter(data));
        parse_points(sample, back_inserter(data));
        parse_points(sample, back_inserter(data));
    } catch (char const* sz) { std::cerr << "Parse failed at '" << sz << "'\n"; }

    std::cout << "data.size(): " << data.size() << " elements\n";
}
