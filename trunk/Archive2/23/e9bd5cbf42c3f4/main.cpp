#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <vector>
#include <map>

namespace qi = boost::spirit::qi;
namespace ascii=boost::spirit::ascii;

typedef std::multimap< std::string,std::string > TMap;

struct SMapInsert
{
    //since you have BOOST_RESULT_OF_USE_DECLTYPE you don't need a nested result struct

    template <typename Map,typename Keys,typename Vals>
    void operator()( Map& out, Keys& keys, Vals& vals ) const
    {
		for(const auto& key : keys)
			for(const auto& val : vals)
				out.insert(TMap::value_type(key,val));
		
    }
};

boost::phoenix::function< SMapInsert > inserter;

int main()
{
    std::string input = "{A [B C] -> F [D E], C ->E,B->Z}";
    TMap data;

    std::string::const_iterator iter = input.begin();
    std::string::const_iterator last = input.end();

    qi::rule< std::string::const_iterator,std::string() > token=+qi::alnum;
    qi::rule< std::string::const_iterator,ascii::space_type,std::vector< std::string >() > 
        keyOrvalue = +( token  | ( '[' >> qi::lexeme[ +qi::char_("a-zA-Z0-9 ") ] >> ']' ) );
    qi::rule< std::string::const_iterator,ascii::space_type, TMap() > 
        root = '{' >> ( ( keyOrvalue >> "->" >> keyOrvalue )[ inserter( qi::_val, qi::_1, qi::_2 ) ] ) % ',' >> '}';
    std::cout << "input: `" << input << "`" << std::endl;
    if( qi::phrase_parse( iter, last, root, ascii::space, data ) && iter==last )
    {
        for( const auto &keyValue : data )
            std::cout << std::left << std::setw(10) << keyValue.first << std::setw(10) << keyValue.second << std::endl;
    } 
    else
        std::cout << "parsing failed:" << std::string( iter,last ) << std::endl;        

    return 0;
}