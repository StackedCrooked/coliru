#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Point {
    float x,y;
    constexpr Point(float x,float y) : x(x), y(y) {}
};

template <typename OI>
static inline void parse_points(char const* szInput, OI out) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    if (!qi::phrase_parse(
                szInput, std::numeric_limits<char const*>::max(), // just wait for NUL char
                *(qi::double_ >> ',' >> qi::double_) 
                    [ *phx::ref(out) = phx::construct<Point>(qi::_1, qi::_2) ]
                >> &qi::lit('\0'),
                qi::space))
    {
        throw szInput; // TODO proper error handling?
    }
}

#include <boost/function_output_iterator.hpp>

int main() {
    try {
        int count = 0;
        parse_points( " 10,9 2.5, 3   4 ,150.32    ", boost::make_function_output_iterator([&](Point const&){count++;}));
        std::cout << "elements in sample: " << count << "\n";
    } catch(char const* sz)
    {
        std::cout << "Parsing failed at '" << sz << "'\n";
    }
}
