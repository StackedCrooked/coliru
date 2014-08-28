#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define FOO(...)                                \
    BOOST_PP_ENUM(                              \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),    \
        MACRO,                                  \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__) \
    )
    
#define MACRO(z, n, data) \
    BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(n, data)), BOOST_PP_TUPLE_ELEM(n, data)
    
FOO(a, b, a+b)