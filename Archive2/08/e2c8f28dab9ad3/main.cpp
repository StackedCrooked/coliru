#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace qi=boost::spirit::qi;
namespace ascii=boost::spirit::ascii;

struct key_value
{
    std::vector<std::string> keys;
    std::vector<std::string> values;
};

struct intermediate_struct
{
    std::vector<key_value> data;
};

BOOST_FUSION_ADAPT_STRUCT(
    key_value,
    (std::vector<std::string>, keys)
    (std::vector<std::string>, values)
)

BOOST_FUSION_ADAPT_STRUCT(
    intermediate_struct,
    (std::vector<key_value>, data)
)

namespace boost{ namespace spirit{ namespace traits
{

    template <>
    struct transform_attribute<std::multimap<std::string,std::string>,intermediate_struct,qi::domain>
    {
        typedef intermediate_struct type;
        
        static type pre(std::multimap<std::string,std::string>& ){ return intermediate_struct();}
        static void post(std::multimap<std::string,std::string>& map, intermediate_struct const& intermediate)
        {
            for(const auto& key_val : intermediate.data)
        {
            for(const auto& key : key_val.keys)
            {
                for(const auto& val : key_val.values)
                {
                    map.insert(typename std::multimap<std::string,std::string>::value_type(key,val));
                }
            }
        }
        }  
        static void fail(std::multimap<std::string,std::string>&){} 
    };

}}}

int main()
{
    std::string input = "{A [B C] -> F [D E], C ->E,B->Z}";
    std::string::const_iterator iter = input.begin(), end = input.end();

    std::multimap<std::string,std::string> sdmap;
    
    qi::rule<std::string::const_iterator,std::string(),ascii::space_type> text_rule = +qi::char_("a-zA-Z0-9") | qi::lexeme[('[' >> +qi::char_("a-zA-Z0-9 ") >> ']')];
    qi::rule<std::string::const_iterator,std::vector<std::string>(),ascii::space_type> keys_rule = +text_rule;
    qi::rule<std::string::const_iterator,std::vector<std::string>(),ascii::space_type> values_rule = +text_rule;
    qi::rule<std::string::const_iterator,intermediate_struct(),ascii::space_type> map_rule = qi::eps >> ('{' >> (keys_rule >> "->" >> values_rule)%',' >> '}');
    
    BOOST_SPIRIT_DEBUG_NODES( (map_rule)(keys_rule)(values_rule) );

    bool r = qi::phrase_parse(  iter, 
                            end,
                            map_rule,
                            ascii::space,
                            sdmap
                        );

    if(r && (iter == end)) {
        std::cout << "Parsing succeeded!" << std::endl;
        for(const auto& pair : sdmap) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    } else {
        std::cout << "Parsing Failed!" << std::endl;   
        std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
    }
    
    return 0;
}