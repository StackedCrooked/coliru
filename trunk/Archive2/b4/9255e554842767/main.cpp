#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

//#include <vector>
//#include <algorithm>

#define MACRO(...)                                                \
    std::find(                                                    \
        BOOST_PP_ENUM(                                            \
            BOOST_PP_DIV(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 2), \
            ENUM_MACRO,                                           \
            BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__)))

#define ENUM_MACRO(z, n, data)                                            \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_CAT(                                                     \
            BOOST_PP_TUPLE_ELEM(BOOST_PP_MUL(n, 2), data),                \
            BOOST_PP_TUPLE_ELEM(BOOST_PP_INC(BOOST_PP_MUL(n, 2)), data)), \
        Type)

typedef int FirstNameType;
typedef std::vector<int>::iterator SecondNameType;
typedef std::vector<int>::iterator ThirdNameType;

int main() {
    std::vector<int>();
    auto it = MACRO(First, Name, Second, Name, Third, Name);
    return 0;
}