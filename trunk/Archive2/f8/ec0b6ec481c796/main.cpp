#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace client {
    namespace qi    = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    struct GateStruct {
        int numberOfInputs;
        std::string gateName;
        std::vector<std::string> wireNames_first;
        std::vector<std::string> wireNames_second;
    };
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
    struct gate_parser : qi::grammar<Iterator, GateStruct(), ascii::space_type> {
        gate_parser() : gate_parser::base_type(start) {
            using qi::int_;
            using qi::lit;
            using ascii::char_;

            wirenameString = +char_("a-zA-Z_0-9"); // lexeme implicit because no skipper
            numberString   = "(" >> int_ >> *(',' >> lit('0')) >> ')';
            wireList       = ('{' >> wirenameString % ',' >> '}')
                        | wirenameString;

            start %= qi::lexeme[ "fanout_n" ]
                     >> '#' >> numberString
                     >> wirenameString >> '(' >> wireList >> ',' >> wireList >> ");"
                   ;

            BOOST_SPIRIT_DEBUG_NODES( (start)(numberString)(wirenameString)(wireList) )
        }
      private:

        qi::rule<Iterator , int(),                      ascii::space_type>  numberString;
        qi::rule<Iterator , std::string()               /* lexeme */>       wirenameString;
        qi::rule<Iterator , std::vector<std::string>(), ascii::space_type>  wireList;
        qi::rule<Iterator , GateStruct(),               ascii::space_type>  start;
    };

}

int main() 
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::gate_parser<iterator_type> gate_parser;

    gate_parser g;
    std::string str;
    while(getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }

        client::GateStruct gate;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, g, space, gate);

        if(r) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "\n-------------------------\n";
        } else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
        if (iter != end)
            std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";
    }

    std::cout << "Bye...\n";
}



