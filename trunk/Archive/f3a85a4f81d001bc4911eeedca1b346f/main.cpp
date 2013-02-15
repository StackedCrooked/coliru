#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <iostream>

#define NUM(...) NUM_SEQ(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) 
#define NUM_SEQ(seq) BOOST_PP_SEQ_FOLD_LEFT(NUM_FOLD, BOOST_PP_SEQ_HEAD(seq), BOOST_PP_SEQ_TAIL(seq)) 
#define NUM_FOLD(_, acc, x) BOOST_PP_CAT(acc, x)

int main()
{
    std::cout << NUM(123,456,789);
}