#include <iostream>
#include <utility>
#include <type_traits>

    void foo(char const*, std::true_type /*is_pointer*/) {
      std::cout << "is pointer\n";
    }
    template<class T, size_t N>
    void foo( T(&)[N], std::false_type /*is_pointer*/) {
      std::cout << "is array\n";
    }
    template<class X>
    void foo( X&& x ) {
      foo( std::forward<X>(x), std::is_pointer<std::remove_reference_t<X>>{} );
    }
    
int main() {
    char* ptr;
    char data[]="abc";
    
    foo(ptr);
    foo(data);
    foo("raw array");
}
