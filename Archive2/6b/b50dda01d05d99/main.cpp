#include <boost/preprocessor.hpp>
#include <iostream>

#define RF_FACTORIZE_PRED_1(_1, state)                                         \
    BOOST_PP_EQUAL(BOOST_PP_MOD(BOOST_PP_TUPLE_ELEM(3, 0, state),              \
                                BOOST_PP_TUPLE_ELEM(3, 1, state)),             \
                   0)

#define RF_FACTORIZE_OP_1(_1, state)                                           \
    (BOOST_PP_DIV(BOOST_PP_TUPLE_ELEM(3, 0, state),                            \
                  BOOST_PP_TUPLE_ELEM(3, 1, state)),                           \
     BOOST_PP_TUPLE_ELEM(3, 1, state),                                         \
     BOOST_PP_LIST_CONS(BOOST_PP_TUPLE_ELEM(3, 1, state),                      \
                        BOOST_PP_TUPLE_ELEM(3, 2, state)))

#define RF_FACTORIZE_PRED_2(_1, state)                                         \
    BOOST_PP_GREATER(BOOST_PP_TUPLE_ELEM(3, 0, state), 1)

#define RF_FACTORIZE_OP_2_LOOP(state)                                          \
    BOOST_PP_WHILE(RF_FACTORIZE_PRED_1, RF_FACTORIZE_OP_1, state)

#define RF_FACTORIZE_OP_2(_1, state)                                           \
    (BOOST_PP_TUPLE_ELEM(3, 0, RF_FACTORIZE_OP_2_LOOP(state)),                 \
     BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(3, 1, state)),                           \
     BOOST_PP_TUPLE_ELEM(3, 2, RF_FACTORIZE_OP_2_LOOP(state)))

#define RF_FACTORIZE(n)                                                        \
    BOOST_PP_TUPLE_ELEM(3, 2,                                                  \
                        BOOST_PP_WHILE(RF_FACTORIZE_PRED_2, RF_FACTORIZE_OP_2, \
                                       (n, 2, BOOST_PP_NIL)))

#define RF_PRINT(_1, _2, x) std::cout << x << ' ';

#define RF_PRINT_FACTORS(_1, n, _2)                                            \
    std::cout << n << ": ";                                                    \
    BOOST_PP_LIST_FOR_EACH(RF_PRINT, ~, RF_FACTORIZE(n));                      \
    std::cout << '\n';

int main() {
    BOOST_PP_REPEAT(50, RF_PRINT_FACTORS, ~);
    return 0;
}
