#include <type_traits>
#include <tuple>
#include <iostream>

int main(){
    auto l = [](int i){ return i * 42; };
    typedef std::tuple<decltype(l)> tuple_t;
    
    static_assert(std::is_empty<tuple_t>(), "non-empty tuple with empty lambda");
    
    struct is_it_really {
        tuple_t t;
    };
    
    static_assert(std::is_empty<is_it_really>(), "non-empty struct containing tuple with empty lambda");

}