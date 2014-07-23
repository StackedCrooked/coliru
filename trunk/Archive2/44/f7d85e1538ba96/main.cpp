#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define VA_TYPES_WITH_ARGS(...)   \
    BOOST_PP_ENUM(                \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),    \
        VA_TYPES_WITH_ARGS_MACRO,               \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__) \
    )
    
#define VA_TYPES_WITH_ARGS_MACRO(z, n, data)       \
    BOOST_PP_TUPLE_ELEM(n, data) BOOST_PP_CAT(     \
        _arg,                                      \
        BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(data), n) \
    )                                              
    
VA_TYPES_WITH_ARGS(int, bool, float)