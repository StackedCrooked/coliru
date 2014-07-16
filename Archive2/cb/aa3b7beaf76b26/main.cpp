#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define PRINT_COMMAS(...)\
    BOOST_PP_REPEAT( \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), \
        PRINT_COMMAS_MACRO, \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__))
        
#define PRINT_COMMAS_MACRO(z, n, data) ,

PRINT_COMMAS(,,,,)
