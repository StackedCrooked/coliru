#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>

#define FIRST_PAIR_WITH_ELEM_MACRO(z, n, data)      \
    BOOST_PP_IF(                                    \
        BOOST_PP_EQUAL(                             \
            BOOST_PP_TUPLE_ELEM(                    \
                0,                                  \
                BOOST_PP_TUPLE_ELEM(                \
                    n,                              \
                    BOOST_PP_TUPLE_ELEM(0, data))), \
            BOOST_PP_TUPLE_ELEM(1, data)),          \
        BOOST_PP_TUPLE_ELEM(                        \
            1,                                      \
            BOOST_PP_TUPLE_ELEM(                    \
                n,                                  \
                BOOST_PP_TUPLE_ELEM(0, data))), )

#define FIRST_PAIR_WITH_ELEM(pairs, elem) \
    BOOST_PP_REPEAT(                      \
        BOOST_PP_TUPLE_SIZE(pairs),       \
        FIRST_PAIR_WITH_ELEM_MACRO,       \
        (pairs, elem))

#define NAMED_MACRO(macro, ...) \
    macro(                      \
        (NAMED_MACRO_IMPL(__VA_ARGS__)))

#define NAMED_MACRO_IMPL(...)                \
    BOOST_PP_ENUM(                           \
        BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), \
        NAMED_MACRO_ENUM_MACRO,              \
        BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__))

#define NAMED_MACRO_ENUM_MACRO(z, n, data) \
    FIRST_PAIR_WITH_ELEM(data, n)
    
///////////////////////////////////////////////////////////////

#include <iostream>

#define TEST_A 0
#define TEST_B 1
#define TEST_C 2
#define TEST_D 3
#define TEST(a, b, c, d) NAMED_MACRO(TEST_IMPL, a, b, c, d)
#define TEST_IMPL(abcd) std::cout << BOOST_PP_TUPLE_ELEM(0, abcd) << ' ' << BOOST_PP_TUPLE_ELEM(1, abcd) << ' ' << BOOST_PP_TUPLE_ELEM(2, abcd) << ' ' << BOOST_PP_TUPLE_ELEM(3, abcd) << '\n'

int main() {
    TEST((TEST_A, "foo"), (TEST_B, "bar"), (TEST_C, "baz"), (TEST_D, "qaz"));
    TEST((TEST_D, "foo"), (TEST_C, "bar"), (TEST_A, "baz"), (TEST_B, "qaz"));
}
