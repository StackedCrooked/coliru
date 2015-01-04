#include <boost/preprocessor.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define TRANSFORM(r, data, elem) BOOST_PP_CAT(data, elem)

#define MACRO(F, ...) \
    BOOST_PP_SEQ_FOR_EACH(TRANSFORM, F, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#include <iostream>

int main()
{
    std::cout << BOOST_PP_STRINGIZE(MACRO(F, A, B, C));
}