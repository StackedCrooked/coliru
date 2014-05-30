// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>

namespace qi = boost::spirit::qi;

struct section_t { 
    std::string name, contents;
    friend std::ostream& operator<<(std::ostream& os, section_t const& s) { return os << "section_t[" << s.name << "] {" << s.contents << "}"; }
};

BOOST_FUSION_ADAPT_STRUCT(section_t, (std::string, name)(std::string, contents))

typedef std::vector<section_t> sections_t;

template <typename It, typename Skipper = qi::space_type>
struct grammar : qi::grammar<It, sections_t(), Skipper>
{
    grammar() : grammar::base_type(start) {
        using namespace qi;
        using boost::spirit::repository::qi::seek;

        section_name_rule = lexeme[+char_("A-Za-z0-9_")];
        section           = section_name_rule >> '{' >> lexeme[*~char_('}')] >> '}';
        start             = *seek [ no_skip[eol] >> hold [section] ];

        BOOST_SPIRIT_DEBUG_NODES((start)(section)(section_name_rule))
    }
  private:
    qi::rule<It, sections_t(),  Skipper> start;
    qi::rule<It, section_t(),   Skipper> section;
    qi::rule<It, std::string(), Skipper> section_name_rule;
};

int main() {
    using It = boost::spirit::istream_iterator;
    It f(std::cin >> std::noskipws), l;

    sections_t sections;
    if (qi::phrase_parse(f, l, grammar<It>(), qi::space, sections))
    {
        for(auto& s : sections)
            std::cout << "Parsed: " << s << "\n";
    }
    if (f != l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
