#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <fstream>
#include <iostream>
#include <boost/spirit/repository/include/qi_seek.hpp>

//


namespace client {
    namespace qi    = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace repo = boost::spirit::repository;
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
   
//////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::vector<GateStruct> gateVector;



template <typename Iterator>
    struct gate_parser : qi::grammar<Iterator, gateVector(), ascii::space_type> {
        gate_parser() : gate_parser::base_type(start) {
            using qi::int_;
            using qi::lit;
            using ascii::char_;

            wirenameString = +char_("a-zA-Z_0-9"); // lexeme implicit because no skipper
            numberString   = "(" >> int_ >> *(',' >> lit('0')) >> ')';
       //     numberString   = "(" >> int_ >> qi::omit[int_ % ','] >> ')';

            wireList       = ('{' >> wirenameString % ',' >> '}')
                        | wirenameString;

            gateStruct %= (qi::lexeme[ "fanout_n" ] | qi::lexeme["pin"] |qi::lexeme["pout"] |qi::lexeme["and_n"] |qi::lexeme["notg"]
                           |qi::lexeme["nor_n"]|qi::lexeme["bufg"]|qi::lexeme["or_n"] |qi::lexeme["xor_n"] |qi::lexeme["xnor_n"]
                           |qi::lexeme["nand_n"] )
                     >> '#' >> numberString
                     >> wirenameString >> '(' >> wireList >> ',' >> wireList >> ");" //>> qi::eol
					 
                   ;
				   
                      // start %= gateStruct >> *gateStruct;
                        start %= *repo::qi::seek[gateStruct];
						

          //  BOOST_SPIRIT_DEBUG_NODES( (start)(numberString)(wirenameString)(wireList)(gateStruct))
        }
      private:

        qi::rule<Iterator , int(),                      ascii::space_type>  numberString;
        qi::rule<Iterator , std::string()               /* lexeme */>       wirenameString;
        qi::rule<Iterator , std::vector<std::string>(), ascii::space_type>  wireList;
        qi::rule<Iterator , GateStruct(),               ascii::space_type>  gateStruct;
                qi::rule<Iterator , gateVector() , ascii::space_type> 	start;
    };

	
}

int main()
{
    using boost::spirit::ascii::space;
    //typedef std::string::const_iterator iterator_type;
   // typedef client::gate_parser<iterator_type> gate_parser;

   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    // open file, disable skipping of whitespace
  //  client::gateVector::iterator iterator;
    std::ifstream in("input.txt");
    in.unsetf(std::ios::skipws);

    // wrap istream into iterator
    boost::spirit::istream_iterator begin(in);
    boost::spirit::istream_iterator end;
    client::gateVector gate;
    client::gate_parser<boost::spirit::istream_iterator> p;

    // use iterator to parse file data
    bool r = boost::spirit::qi::phrase_parse(begin , end  , p , space , gate);

         if(r) {
             std::cout << gate.size();
             std::cout << "-------------------------\n";
             std::cout << "Parsing succeeded\n";
             for (client::gateVector::const_iterator iter = gate.begin() ; iter != gate.end() ; iter++) {
               std::cout << "Number Of Inputs:" << iter->numberOfInputs << std::endl;
               std::cout << "Gate Name:" << iter->gateName << std::endl;
               std::cout << "\n-------------------------\n" << std::endl;
           }

         } else {
             std::cout << "-------------------------\n";
             std::cout << "Parsing failed\n";
             std::cout << "-------------------------\n";
         }
         if (begin != end)
             std::cout << "Remaining unparsed: '" ;


    std::cout << "Bye...\n";
    getchar();
}
