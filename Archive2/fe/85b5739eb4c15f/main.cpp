#include <boost/mpl/vector.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/print.hpp>

template< typename... Args >
void test( const Args&... args )
{
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;
    typedef vector<Args...> args_types;
    typedef typename unique<args_types, boost::is_same<_1, _2> >::type unique_types;
    print< unique_types > x;
}

int main()
{
    int a = 0;
    char b = 0;
    test( a, b, a );
}