    #include <boost/config/warning_disable.hpp>
    #include <boost/spirit/include/qi.hpp>
    #include <boost/spirit/include/phoenix.hpp>
    #include <boost/fusion/include/adapt_struct.hpp>
    #include <boost/fusion/include/io.hpp>

    #include <iostream>
    #include <string>
    #include <vector>
    
    namespace client
    {
        namespace spirit = boost::spirit;
        namespace qi     = boost::spirit::qi;
        namespace ph     = boost::phoenix;
        namespace ascii  = boost::spirit::ascii;
    
        struct summand {
            float factor;
            std::string name;
        };
    }
    
    BOOST_FUSION_ADAPT_STRUCT(client::summand,
                          (float, factor)
                          (std::string, name)
                          )

    namespace client {
    
        template <typename Iterator>
        struct summand_parser : qi::grammar<Iterator, summand(), ascii::space_type>
        {
            summand_parser() : summand_parser::base_type(summand_rule)
            {
                using namespace ascii;
            
                summand_rule = (qi::float_ >> -(-qi::lit('*') >> '[' >> qi::lexeme[alpha >> *alnum] >> ']'))
                    | (qi::attr(0.) >> '[' >> qi::lexeme[alpha >> *alnum] >> ']' >> -(-qi::lit('*') >> qi::omit[qi::float_[ph::at_c<0>(qi::_val) = qi::_1]]));

            }
        
            qi::rule<Iterator, summand(), ascii::space_type> summand_rule;
        };
    }
    
    void parseSummandsInto(std::string const& str, client::summand& summands)
    {
        typedef std::string::const_iterator It;
        static const client::summand_parser<It> g;
    
        It iter = str.begin(),
        end = str.end();
    
        bool r = phrase_parse(iter, end, g, boost::spirit::ascii::space, summands);
    
        if (r && iter == end)
            return;
        else
            throw "Parse failed";
    }
        
    int main()
    {
        std::vector<std::string> inputStrings = {"7.5*[someAlphanumStr]", "7.5[someAlphanumStr]", "[someAlphanumStr]*7.4", "[someAlphanumStr]5", "7.4", "[someAlphanumStr]"};
    
        std::for_each(inputStrings.begin(), inputStrings.end(), [&inputStrings](std::string & inputStr) {
            client::summand parsed;
            parseSummandsInto(inputStr, parsed);
            std::cout << inputStr << " -> " << boost::fusion::as_vector(parsed) << std::endl;
        });
    }