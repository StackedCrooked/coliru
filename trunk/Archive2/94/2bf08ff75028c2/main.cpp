#include <iostream>

#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

const int f_const_int() {return 1;}

template <typename T>
struct return_type;
template <typename R>
struct return_type<R(*)()> { typedef R type; };

int main()
{
    typedef return_type<BOOST_TYPEOF(&f_const_int)>::type type;
    BOOST_STATIC_ASSERT( not boost::is_same<type, int>::value );
    BOOST_STATIC_ASSERT( boost::is_same<type, const int>::value );
}
