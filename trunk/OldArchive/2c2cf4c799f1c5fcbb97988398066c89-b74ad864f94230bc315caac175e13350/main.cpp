#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <iomanip>
#include <memory>

#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;
namespace ascii = boost::spirit::ascii;

typedef qi::rule<std::string::const_iterator,ascii::space_type> mrule_t;
typedef qi::rule<std::string::const_iterator,std::string() >    wrule_t;

struct TStruct
{
    mrule_t     rule_;
    template<typename T, typename R>
    TStruct( T& rVar,const std::string&name, const R& rule ) :
        rule_( rule[ ph::ref(rVar) = qi::_1 ] )
    {
        rule_.name(name);
    	qi::debug(rule_);
    }
};

bool mparse(const std::string& line, const std::vector<TStruct>& args )
{
   qi::symbols<char,const mrule_t*> options;
	for( const auto &argsx : args )
		options.add(argsx.rule_.name(),&(argsx.rule_));
    auto f = begin(line), l=end(line);
	qi::rule<std::string::const_iterator,qi::locals<const mrule_t*>,ascii::space_type> parser = options[qi::_a=qi::_1] >> qi::lazy(*qi::_a);
	
    return  qi::phrase_parse( f, l, +parser, ascii::space ) && f==l;
}

int main()
{
    wrule_t rword=+~ascii::space;

    std::string par1,par2,par3,par4;

    std::vector< TStruct > args{
        { par1, "-a", rword },
        { par2, "-b", rword },
        { par3, "-c", rword },
        { par4, "-d", rword }
    };

    std::vector< std::string > inputs{
        "-a atoken -b btoken -c ctoken -d dtoken",
        "-b btoken -c ctoken -d dtoken -a atoken",
        "-b btoken -c ctoken -d dtoken",
        "-b btoken -c ctoken",
        "-c ctoken -d dtoken -a atoken -b btoken",
        "-d dtoken -a atoken -b btoken -c ctoken",
        "-a atoken",
        "-b btoken",
        "-c ctoken",
        "-d dtoken"
    };

    for ( const auto& input : inputs )
    {
        std::cout << "processing input:" << input << std::endl;
        par1=par2=par3=par4="";
        if( mparse( input,args ) )
        {
            std::cout << "par1:" << par1 << std::endl;
            std::cout << "par2:" << par2 << std::endl;
            std::cout << "par3:" << par3 << std::endl;
            std::cout << "par4:" << par4 << std::endl;
			std::cout << std::endl << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}