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

#include <boost/function_output_iterator.hpp>

int main() {
    try {
        int count = 0;
        parse_points( boost::make_function_output_iterator([&](Point const&){count++;}), " 10,9 2.5, 3   4 ,150.32    ");
        std::cout << "elements in sample: " << count << "\n";
    } catch(char const* sz)
    {
        std::cout << "Parsing failed at '" << sz << "'\n";
    }
}
