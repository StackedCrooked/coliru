#include <iostream>
#include <boost/preprocessor.hpp>

#define PRINT_ONE(elem) BOOST_PP_STRINGIZE(elem) " = " << elem
#define PRINT_ONE_COMMA(r, data, elem) BOOST_PP_STRINGIZE(elem) " = " << elem << ", " <<

#define LAST(seq) BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
#define REST(seq) BOOST_PP_SEQ_SUBSEQ(seq, 0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)))
#define PRINT(seq) std::cout << BOOST_PP_SEQ_FOR_EACH(PRINT_ONE_COMMA, _ ,REST(seq)) PRINT_ONE(LAST(seq)) << '\n';

int main() {
    int a = 5, b = 3, c = 7;
    PRINT((a)(b)(c));
}