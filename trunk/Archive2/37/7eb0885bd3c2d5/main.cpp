#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define PRINT_COMMAS(...)\
    BOOST_PP_ENUM( \
        BOOST_PP_INC(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), \
        BOOST_PP_TUPLE_EAT(), \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__))

PRINT_COMMAS(,,,,)
