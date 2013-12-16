#include <type_traits>

template <int> struct empty {};
    
int main( ) {
 
    static_assert(std::is_empty<empty<0>>::value, "empty<0> is an empty type");
    static_assert(sizeof(empty<0>) == 0, "empty<0> doesn't have zero size");

}

