#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace ph    = boost::phoenix;
namespace ascii = boost::spirit::ascii;
using namespace ph::arg_names;

typedef qi::rule<std::string::const_iterator,ascii::space_type> mrule_t;
typedef qi::rule<std::string::const_iterator,std::string() >    wrule_t;

struct TStruct
{
    mrule_t     rule_;
    template<typename T,typename R>
    TStruct( T& rVar,const std::string&name, R& rule ) :
        rule_( qi::lit(name) >> rule[ ph::ref(rVar) = qi::_1 ] )
    { 
        rule_.name(name);
        // debug(rule_);
    }
};

struct DeepCopy
{
    template<typename E> struct result { typedef typename boost::proto::result_of::deep_copy<E>::type type; };

    template<typename E>
        typename result<E>::type
        operator()(E const& expr) const {
            return boost::proto::deep_copy(expr);
        }
};

static const ph::function<DeepCopy> deepcopy_;

template<typename ...Tail>
void mparse(const std::string& line,Tail& ...tail)
{
    auto parser = boost::fusion::fold(
                boost::tie(ph::bind(&TStruct::rule_, arg1)(tail)...),
                qi::eps(false),
                deepcopy_(arg2 | arg1)
            );

    auto f=begin(line), l=end(line);

    if( qi::phrase_parse(f, l, parser, ascii::space ) )
        std::cout << "Parsed:" << line << std::endl;
    else
        std::cout << "Syntax error:" << line << std::endl;

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}

int main()
{
    wrule_t rword=+~ascii::space;

    std::string par1,par2,par3,par4;

    TStruct r1( par1, "-a", rword );
    TStruct r2( par2, "-b", rword );
    TStruct r3( par3, "-c", rword );
    TStruct r4( par4, "-d", rword );

    mparse("abc 8.81"   ,r1,r2,r3,r4);
    mparse("-a atoken"  ,r1,r2,r3,r4);
    mparse("-b btoken"  ,r1,r2,r3,r4);
    mparse("-c ctoken"  ,r1,r2,r3,r4);
    mparse("-d dtoken"  ,r1,r2,r3,r4);

    std::cout << "Bye\n";
}
