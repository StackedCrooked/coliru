#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <iomanip>
#include <utility>
#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_eps.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/make_vector.hpp>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;


template <typename Attr, typename Parser>
struct TStruct
{
    typename boost::proto::result_of::deep_copy<decltype(qi::lit(std::string())>>std::declval<Parser>()[std::declval<typename ph::expression::reference<Attr>::type>()=qi::_1] )>::type parser;
    TStruct( Attr& attr,const std::string&name, const Parser& p ) :
        parser( boost::proto::deep_copy(qi::lit(name) >> p[ ph::ref(attr) = qi::_1 ]) )
    {
        
    }
};

template <typename Attr, typename Parser>
auto make_tstruct(Attr& attr, const std::string& name, const Parser& p) -> decltype(TStruct<Attr,Parser>(attr,name,p))
{
    return TStruct<Attr,Parser>(attr,name,p);
}

struct join
{
	template <typename State, typename StructT>
	auto operator()(const State& state, const StructT& struct_) const -> decltype (boost::proto::deep_copy(struct_.parser^state))
	{
		return boost::proto::deep_copy(struct_.parser^state);
	}
};

template <typename Sequence>
bool mparse(const std::string& line,const Sequence& args )
{
	auto parser = fusion::fold( 
							args,
							qi::eps(false),
							join()
				);
    auto f = begin(line), l=end(line);
    return  qi::phrase_parse( f, l, parser, ascii::space ) && f==l;
}

int main()
{
    auto rword=qi::as_string[qi::lexeme[+~ascii::space]]; //Need to explicitly say that it is a string and not a vector<char>, also need to limit the greediness
    auto rint=qi::int_;
    
    std::string mixedpar1,mixedpar2;
    int mixedpar3;
    
    auto mixedargs = fusion::make_vector(
        make_tstruct( mixedpar1, "-a", rword ),
        make_tstruct( mixedpar2, "-b", rword ),
        make_tstruct( mixedpar3, "-c", rint )
    );
    
    std::string mixedinput = "-c 10 -b btoken -a atoken";
    
    if( mparse(mixedinput, mixedargs) )
    {
        std::cout << "par1:" << mixedpar1 << std::endl;
        std::cout << "par2:" << mixedpar2 << std::endl;
        std::cout << "par3:" << mixedpar3 << std::endl;
    }

    //YOUR CODE
    std::string par1,par2,par3,par4;

    auto args = fusion::make_vector(
        make_tstruct( par1, "-a", rword ),
        make_tstruct( par2, "-b", rword ),
        make_tstruct( par3, "-c", rword ),
        make_tstruct( par4, "-d", rword )
    );

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
        }
        std::cout << std::endl;
    }

    return 0;
}