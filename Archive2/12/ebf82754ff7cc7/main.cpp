#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define MACRO(...)  \
    CompileTimeList< \
    BOOST_PP_ENUM( \
        BOOST_PP_DIV(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 2), \
        ENUM_MACRO, \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__) \
    ) \
    >

#define ENUM_MACRO(z, n, data) \
    BOOST_PP_CAT( \
        BOOST_PP_CAT( \
            BOOST_PP_TUPLE_ELEM(BOOST_PP_MUL(n, 2), data), \
            BOOST_PP_TUPLE_ELEM(BOOST_PP_INC(BOOST_PP_MUL(n, 2)), data) \
        ), \
        Type \
    )
        

MACRO(a, b, c, d)