#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define TEST(...)\
    BOOST_PP_REPEAT( \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), \
        MACRO, \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__))

#define MACRO(z, n, data) BOOST_PP_IF(1,BOOST_PP_COMMA,BOOST_PP_TUPLE_EAT())()

TEST(1,2,3,4)
