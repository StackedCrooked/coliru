#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/stringize.hpp>

#define OP(s, state, x) BOOST_PP_CAT(state##_, x)
#define CONCAT_SEQ(s) BOOST_PP_SEQ_FOLD_LEFT(OP, BOOST_PP_SEQ_HEAD(s), BOOST_PP_SEQ_TAIL(s))
#define CONCAT_TUPLE(t) CONCAT_SEQ(BOOST_PP_TUPLE_TO_SEQ(t))

#include <iostream>
int main()
{
    std::cout << BOOST_PP_STRINGIZE(CONCAT_TUPLE((a, b, c, d)));
}