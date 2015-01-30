#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/static_assert.hpp>

const int f_const_int() {return 1;}

int main()
{
    typedef boost::function_traits<BOOST_TYPEOF(f_const_int)>::result_type type;
    BOOST_STATIC_ASSERT( not boost::is_same<type, int>::value );
    BOOST_STATIC_ASSERT( boost::is_same<type, const int>::value );
}
