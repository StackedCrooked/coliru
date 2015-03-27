//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iomanip>

namespace qi = boost::spirit::qi;
namespace ascii = qi::ascii;

namespace ast {
    struct JEDEC {
        std::string caption;
        struct field { 
            char id;
            std::string value;
        };
        std::vector<field> fields;
        uint16_t checksum;
    };

    inline static std::ostream& operator<<(std::ostream& os, JEDEC const& jedec) {
        os << "Start: " << jedec.caption << "*\n";
        for(auto& f : jedec.fields)
            os << f.id << " " << f.value << "*\n";

        auto saved = os.rdstate();
        os << "End: " << std::hex << std::setw(4) << std::setfill('0') << jedec.checksum;
        os.setstate(saved);

        return os;
    }
}

BOOST_FUSION_ADAPT_STRUCT(ast::JEDEC::field,
        (char, id)(std::string, value))
BOOST_FUSION_ADAPT_STRUCT(ast::JEDEC,
        (std::string, caption)
        (std::vector<ast::JEDEC::field>, fields)
        (uint16_t, checksum))

template <typename It> 
struct JedecGrammar : qi::grammar<It, ast::JEDEC(), ascii::space_type>
{
    JedecGrammar() : JedecGrammar::base_type(start) {
        const char STX = '\x02';
        const char ETX = '\x03';

        value = *(ascii::char_("\x20-\x7e\r\n") - '*') >> '*';
        field = ascii::graph >> value;
        start = STX >> value >> *field >> ETX >> xmit_checksum; 

        BOOST_SPIRIT_DEBUG_NODES((start)(field)(value))
    }
  private:
    qi::rule<It, ast::JEDEC(), ascii::space_type> start;
    qi::rule<It, ast::JEDEC::field()>             field;
    qi::rule<It, std::string()>                   value;
    qi::uint_parser<uint16_t, 16, 4, 4>           xmit_checksum;
};

int main() {
    typedef boost::spirit::istream_iterator It;
    It first(std::cin>>std::noskipws), last;
    
    JedecGrammar<It> g;

    ast::JEDEC jedec;
    bool ok = phrase_parse(first, last, g, ascii::space, jedec);

    if (ok)
    {
        std::cout << "Parse success\n";
        std::cout << jedec;
    }
    else
        std::cout << "Parse failed\n";

    if (first != last)
        std::cout << "Remaining input unparsed: '" << std::string(first, last) << "'\n";
}

