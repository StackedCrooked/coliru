#define BOOST_PP_VARIADICS
#include <boost/preprocessor/tuple/enum.hpp>

#define FOO(a, b, c) a-b-c
//#define FOO(...) __VA_ARGS__

#define BAR(tup) FOO(BOOST_PP_TUPLE_ENUM(tup))

BAR((1, 2, 3))