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
        namespace qi = boost::spirit::qi;
        using namespace qi;

        rule<It, record_struct(), locals<uint8_t>, space_type> g;

        g %= lexeme[+(alnum | '_')]
             >> uint_ [_a = _1] >> (uint_ | attr(_a))
             >> -("//" >> lexeme[+char_]);

        parsed = phrase_parse(iter, end, g, space, result);
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
