#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace client {
    namespace qi    = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phx   = boost::phoenix;

    struct GateStruct {
        int numberOfInputs;
        std::string gateName;
        std::vector<std::string> wireNames_first;
        std::vector<std::string> wireNames_second;
    };

    typedef std::vector<GateStruct> GateStructs;
}

BOOST_FUSION_ADAPT_STRUCT(client::GateStruct ,
                          (int ,numberOfInputs)
                          (std::string, gateName)
                          (std::vector<std::string>, wireNames_first)
                          (std::vector<std::string>, wireNames_second)
                         )

namespace client 
{
    template <typename Iterator>
    struct gate_parser : qi::grammar<Iterator, GateStructs(), ascii::blank_type> {
        gate_parser() : gate_parser::base_type(start) {
            using qi::int_;
            using qi::lit;
            using qi::omit;
            using qi::_1;
            using qi::_val;
            using phx::push_back;
            using ascii::char_;
            using qi::eol;

            wirenameString = +char_("a-zA-Z_0-9"); // lexeme implicit because no skipper
            numberString   = "(" >> int_ >> *(',' >> lit('0')) >> ')';
            wireList       = ('{' >> wirenameString % ',' >> '}')
                           | wirenameString;

            fanout_n       = qi::lexeme[ "fanout_n" ]
                           >> '#' >> numberString
                           >> wirenameString >> '(' >> wireList >> ',' >> wireList >> ");"
                           ;

            other_line     = *(char_ - eol);

            start          = 
                           (   fanout_n [ phx::push_back(_val, _1) ]
                             | other_line
                           ) % eol
                           ;

            BOOST_SPIRIT_DEBUG_NODES( (start)(fanout_n)(other_line)(numberString)(wirenameString)(wireList) )
        }
      private:

        qi::rule<Iterator , int(),                         ascii::blank_type>  numberString;
        qi::rule<Iterator , std::string()                  /* lexeme */>       wirenameString;
        qi::rule<Iterator , std::vector<std::string>(),    ascii::blank_type>  wireList;
        qi::rule<Iterator , GateStruct(),                  ascii::blank_type>  fanout_n;
        qi::rule<Iterator , /*GateStruct(),       */       ascii::blank_type>  other_line;
        qi::rule<Iterator , GateStructs(),                 ascii::blank_type>  start;
    };

}

int main() 
{
    using boost::spirit::ascii::blank;
    typedef boost::spirit::istream_iterator iterator_type;
    typedef client::gate_parser<iterator_type> gate_parser;

    gate_parser g;
    iterator_type iter(std::cin >> std::noskipws), end;

    client::GateStructs gates;
    bool r = phrase_parse(iter, end, g, blank, gates);

    if(r) {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded: " << gates.size() << " gates\n";
        std::cout << "\n-------------------------\n";
    } else {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
    if (iter != end)
        std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";

    std::cout << "Bye...\n";
}
#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace client {
    namespace qi    = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phx   = boost::phoenix;

    struct GateStruct {
        int numberOfInputs;
        std::string gateName;
        std::vector<std::string> wireNames_first;
        std::vector<std::string> wireNames_second;
    };

    typedef std::vector<GateStruct> GateStructs;
}

BOOST_FUSION_ADAPT_STRUCT(client::GateStruct ,
                          (int ,numberOfInputs)
                          (std::string, gateName)
                          (std::vector<std::string>, wireNames_first)
                          (std::vector<std::string>, wireNames_second)
                         )

namespace client 
{
    template <typename Iterator>
    struct gate_parser : qi::grammar<Iterator, GateStructs(), ascii::blank_type> {
        gate_parser() : gate_parser::base_type(start) {
            using qi::int_;
            using qi::lit;
            using qi::omit;
            using qi::_1;
            using qi::_val;
            using phx::push_back;
            using ascii::char_;
            using qi::eol;

            wirenameString = +char_("a-zA-Z_0-9"); // lexeme implicit because no skipper
            numberString   = "(" >> int_ >> *(',' >> lit('0')) >> ')';
            wireList       = ('{' >> wirenameString % ',' >> '}')
                           | wirenameString;

            fanout_n       = qi::lexeme[ "fanout_n" ]
                           >> '#' >> numberString
                           >> wirenameString >> '(' >> wireList >> ',' >> wireList >> ");"
                           ;

            other_line     = *(char_ - eol);

            start          = 
                           (   fanout_n [ phx::push_back(_val, _1) ]
                             | other_line
                           ) % eol
                           ;

            BOOST_SPIRIT_DEBUG_NODES( (start)(fanout_n)(other_line)(numberString)(wirenameString)(wireList) )
        }
      private:

        qi::rule<Iterator , int(),                         ascii::blank_type>  numberString;
        qi::rule<Iterator , std::string()                  /* lexeme */>       wirenameString;
        qi::rule<Iterator , std::vector<std::string>(),    ascii::blank_type>  wireList;
        qi::rule<Iterator , GateStruct(),                  ascii::blank_type>  fanout_n;
        qi::rule<Iterator , /*GateStruct(),       */       ascii::blank_type>  other_line;
        qi::rule<Iterator , GateStructs(),                 ascii::blank_type>  start;
    };

}

int main() 
{
    using boost::spirit::ascii::blank;
    typedef boost::spirit::istream_iterator iterator_type;
    typedef client::gate_parser<iterator_type> gate_parser;

    gate_parser g;
    iterator_type iter(std::cin >> std::noskipws), end;

    client::GateStructs gates;
    bool r = phrase_parse(iter, end, g, blank, gates);

    if(r) {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded: " << gates.size() << " gates\n";
        std::cout << "\n-------------------------\n";
    } else {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
    if (iter != end)
        std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";

    std::cout << "Bye...\n";
}
