#include <vector>
#include <iostream>

template<typename T>
struct has_value_type {
    
    typedef char(&yes)[1];
    typedef char(&no)[2];
    
    struct Fallback {
        int value_type;    
    };
    
    struct Derived : T, Fallback {};
    
    template<typename U, U>
    struct Check;
    
    template<typename U>
    static no test( Check<int Fallback::*, &U::value_type>* );
    
    template<typename>
    static yes test(...);
    
    static const bool value = sizeof( test<Derived>( 0 ) ) == sizeof(yes);
};

class C : private std::vector<int> {};

int main() {
   std::cout <<  has_value_type<C>::value;
}
