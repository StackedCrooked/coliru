#include <boost/mpl/vector.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/insert.hpp>

template< typename... Args >
void test( const Args&... args )
{
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;
    typedef typename fold< vector<Args...>
        , set0<>
        , insert<_1, _2>
    >::type unique_args;

    static_assert( size<unique_args>::value == sizeof...(Args), "Duplicate argument types" );
}

int main()
{
    test( int(0), char(0), short(1) );
}
