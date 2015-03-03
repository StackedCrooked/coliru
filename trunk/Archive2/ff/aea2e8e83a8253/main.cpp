#include <boost/preprocessor.hpp>

#define TYPEDEF_AUX(r, data, elem) \
    using BOOST_PP_TUPLE_ELEM(2, 1, elem) = BOOST_PP_TUPLE_ELEM(2, 0, elem);

#define TYPEDEF(...) \
    BOOST_PP_SEQ_FOR_EACH(TYPEDEF_AUX, 0, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#include <iostream>
#include <typeinfo>

TYPEDEF(
    (unsigned char, BYTE),
    (unsigned short, WORD),
    (unsigned long, DWORD)
)

int main() {
    std::cout << typeid(BYTE).name() << '\n';
    std::cout << typeid(WORD).name() << '\n';
    std::cout << typeid(DWORD).name() << '\n';
    return 0;
}