#include <string>
#include <cstdint>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct record_struct {
    std::string Name;
    uint8_t Distance;
    uint8_t TravelDistance;
    std::string Comment;
};

BOOST_FUSION_ADAPT_STRUCT(
    record_struct,
    (std::string, Name)
    (uint8_t, Distance)
    (uint8_t, TravelDistance)
    (std::string, Comment)
)

std::ostream &operator<<(std::ostream &o, const record_struct &s) {
    o << s.Name << " (" << +s.Distance << ":" << +s.TravelDistance << ") " << s.Comment;
    return o;
}

bool test(std::string const& s) {
    typedef std::string::const_iterator It;
    It iter = s.begin(), end = s.end();
    record_struct result;

    bool parsed = false;
    {
        namespace qi  = boost::spirit::qi;
        namespace phx = boost::phoenix;
        using namespace qi;

        static const rule<It, uint8_t(uint8_t)> def_uint8 
            = uint_parser<uint8_t>() | attr(_r1);

        parsed = phrase_parse(iter, end, lexeme[+(alnum | '_')]
                >> uint_ >> def_uint8(phx::at_c<1>(_val))
                >> -("//" >> lexeme[+char_]),
             space, result);
    }

    if (parsed) {
        std::cout << "Parsed: " << result << "\n";
    } else {
        std::cout << "Failed\n";
    }

    if (iter!=end) {
        std::cout << "Unparsed: '" << std::string(iter, end) << "'\n";
    }

    return parsed && (iter == end);
}

int main() {
    if (!test("Milan 20 22"))                 return 1;
    if (!test("Paris 8 9 // comment"))        return 1;
    if (!test("London 5"))                    return 1;
    if (!test("Rome 1 //not a real comment")) return 1;
}
