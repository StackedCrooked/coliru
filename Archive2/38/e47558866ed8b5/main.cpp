#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define TEST(...)\
    BOOST_PP_REPEAT( \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), \
        MACRO, \
    )

#define MACRO(z, n, data) MACRO_CONTAINING_COMMA(n,n)

#define MACRO_CONTAINING_COMMA(_NAME, _NAME2) _NAME,_NAME2

TEST(1,2,3,4)