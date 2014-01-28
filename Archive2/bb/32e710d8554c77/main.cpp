#include <tuple>

#define BOOST_PP_VARIADICS 1
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#define UNPACK_VAR_macro(r, DATA, I, ELEM) ::std::tuple_element<I, decltype DATA>::type ELEM;

#define UNPACK(VAR_TUPLE, ...) \
    BOOST_PP_SEQ_FOR_EACH_I(UNPACK_VAR_macro, (__VA_ARGS__), BOOST_PP_TUPLE_TO_SEQ(VAR_TUPLE)) \
    ::std::tie VAR_TUPLE = __VA_ARGS__
    
    
    
#include <iostream>

auto foo() {
    return std::make_tuple(0, 2.0, "test");
}

int main() {
    UNPACK((a,b,c), foo());
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    
    return 0;
}