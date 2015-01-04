#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define TRANSFORM(r, data, elem) data:elem

#define MACRO(F, ...) \
    BOOST_PP_SEQ_FOR_EACH(TRANSFORM, F, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#include <iostream>
#include <boost/preprocessor/stringize.hpp>

int main()
{
    std::cout << BOOST_PP_STRINGIZE(MACRO(F, A, B, C, D, E, G, H, I, J));
}