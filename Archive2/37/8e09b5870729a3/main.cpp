#include <iostream>
#include <boost/preprocessor.hpp>

#define TUP_WITH_0(a, b) BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_ELEM(2, 0, a), 0), a, b))
#define TUP_WITH_1(a, b) BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_IF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_ELEM(2, 0, a), 1), a, b))

#define NAMED2(macro, a, b) macro(TUP_WITH_0(a, b), TUP_WITH_1(a, b))

#define TEST_FOO 0
#define TEST_BAR 1
#define TEST(foo, bar) NAMED2(TEST_IMPL, foo, bar)

#define TEST_IMPL(foo, bar) std::cout << (foo) << (bar);

int main() {
    TEST((TEST_FOO, "foo"), (TEST_BAR, "bar"));
    std::cout << '\n';
    TEST((TEST_BAR, "bar"), (TEST_FOO, "foo"));
}