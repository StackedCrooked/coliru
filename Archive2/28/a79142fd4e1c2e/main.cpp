#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define _ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define HAS_COMMA(...) _ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define _TRIGGER_PARENTHESIS_(...) ,
 
#define ISEMPTY(...)                                                    \
_ISEMPTY(                                                               \
          /* test if there is just one argument, eventually an empty    \
             one */                                                     \
          HAS_COMMA(__VA_ARGS__),                                       \
          /* test if _TRIGGER_PARENTHESIS_ together with the argument   \
             adds a comma */                                            \
          HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__),                 \
          /* test if the argument together with a parenthesis           \
             adds a comma */                                            \
          HAS_COMMA(__VA_ARGS__ (/*empty*/)),                           \
          /* test if placing it between _TRIGGER_PARENTHESIS_ and the   \
             parenthesis adds a comma */                                \
          HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/))      \
          )
 
#define PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _ISEMPTY(_0, _1, _2, _3) HAS_COMMA(PASTE5(_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define _IS_EMPTY_CASE_0001 ,

#define VA_TYPES_WITH_ARGS(...)       \
    BOOST_PP_IF(                      \
        ISEMPTY(__VA_ARGS__),         \
        BOOST_PP_TUPLE_EAT(),         \
        VA_TYPES_WITH_ARGS_IMPL       \
    )(__VA_ARGS__)
    
#define VA_TYPES_WITH_ARGS_IMPL(...) \
    BOOST_PP_ENUM(                   \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),    \
        VA_TYPES_WITH_ARGS_MACRO,               \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__) \
    )
    
#define VA_TYPES_WITH_ARGS_MACRO(z, n, data)       \
    BOOST_PP_TUPLE_ELEM(n, data) BOOST_PP_CAT(     \
        _arg,                                      \
        BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(data), n) \
    )                                              
    
VA_TYPES_WITH_ARGS(int, bool, double)

foo

VA_TYPES_WITH_ARGS()