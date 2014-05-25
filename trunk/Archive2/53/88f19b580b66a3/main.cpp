#include <iostream>
#include <string>
#include <boost/format.hpp>

namespace impl
{
    namespace
    {
        boost::format& out( boost::format& fmt ) { return fmt ;}

        template < typename T >
        boost::format& out( boost::format& fmt, const T& v ) { return fmt % v ;}

        template < typename FIRST, typename... REST >
        boost::format& out( boost::format& fmt, const FIRST& first, const REST&... rest )
        { return out( out( fmt, first ), rest... ) ;}
    }
}

template < typename... ARGS > std::string out( std::string format, const ARGS&... args )
{
    boost::format fmt(format) ;
    impl::out( fmt, args... ) ;

    const std::string result = fmt.str() ;
    // do whatever else with result

    return result ;
}

int main()
{
    std::cout << out( "trivial\n" ) ;
    std::cout << out( "non-trivial: %+d %c %2.2f '%s'\n", 12345, 'A', 67.899, "hello" ) ;
}
