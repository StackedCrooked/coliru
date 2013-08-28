#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_omit.hpp>

#include <iostream>
#include <string>
#include <climits>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename T>
struct min_max_set
{
    min_max_set():min(std::numeric_limits<T>::max()),max(std::numeric_limits<T>::min()),set(){}
	T min;
	T max;
	std::vector<T> set;
};

namespace boost{ namespace spirit { namespace traits
{
	template <typename T>
	struct is_container<min_max_set<T>>
		: boost::mpl::true_
	{};
	
	template <typename T>
	struct container_value<min_max_set<T>>
	{
		typedef T type;
	};
	
	template <typename T>
	struct push_back_container<min_max_set<T>,T>
	{
		static bool call(min_max_set<T>& cont, const T& val)
		{
			if(cont.min>val)
				cont.min=val;
			if(cont.max<val)
				cont.max=val;
			cont.set.push_back(val);
			return true;
		}
	};

}}}

template<typename T,typename R>
void testParser( R rule )
{
    for ( const auto input : std::vector< std::string >{ "5 1.0 2.0 3.0 4.0 5.0", "1 1.0", "0" , "", "2 3 ab" } )
    {
        bool rc;

        auto iter( input.begin() );
        auto last( input.end() );
        min_max_set<T> accum;	
		
        rc = qi::phrase_parse( iter, last,
				qi::omit[qi::int_] >> *rule
                ,ascii::space, accum ) && iter==last;
        std::cout << ( rc ? "ok :`" : "err:`" ) << input << "` -> ";
        if( rc )
        {
            std::cout << "min=" << accum.min << " max=" << accum.max << "\t";
            std::copy( accum.set.begin(), accum.set.end(), std::ostream_iterator<T>( std::cout," " ));
        }
        else
            std::cout << *iter;
        std::cout << std::endl;
    }
}
	
	
int main( int argc, char**argv )
{
    testParser<double>(qi::double_);
    return 0;
}