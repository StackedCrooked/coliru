#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Point {
    float x,y;
    constexpr Point(float x,float y) : x(x), y(y) {}
};

template <typename Out>
static inline void parse_points(char const* szInput, Out out) {
    namespace qi  = boost::spirit::qi;
    namespace phx = boost::phoenix;

    // fake end iterator; we'll watch for NUL char
    static constexpr char const* adnauseam = std::numeric_limits<char const*>::max(); 

    if (!qi::phrase_parse(szInput, adnauseam, 
            *(qi::double_ > ',' > qi::double_) [ *phx::ref(out) = phx::construct<Point>(qi::_1,qi::_2) ]
            > &qi::lit('\0'), qi::space))
    {
        throw szInput; // TODO
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
