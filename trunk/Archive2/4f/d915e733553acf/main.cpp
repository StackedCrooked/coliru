#include <iostream>
#include <tuple>
#include <utility>
#include <array>

    template<bool b>
    using bool_t = std::integral_constant<bool, b>;
    template<size_t n>
    using sizeof_t = std::integral_constant<size_t, n>;
    template<class T>
    using get_sizeof_t = sizeof_t<sizeof(T)>;
    
    template <class T>
    void SwapEndian(T& t, std::true_type /*is pod*/, sizeof_t<4>) {
        std::cout << "4 bytes!\n";
      // code to handle 32 bit pods
    }
    template <class T, size_t n>
    void SwapEndian(T& t, std::true_type /*is pod*/, sizeof_t<n>) {
        std::cout << "pod\n";
      // code to handle generic case
    }
    template <class T, bool b, size_t n>
    void SwapEndian(T& t, bool_t<b>, sizeof_t<n>) {
        std::cout << "generic\n";
      // code to handle generic case
    }
    template<class T>
    void SwapEndian(T& t) {
        SwapEndian(t, std::is_pod<T>{}, get_sizeof_t<T>{});
    }
struct foo {
    foo() {}; // not POD
};
int main() {
    int x; double d; foo f;
    SwapEndian( x );
    SwapEndian( d );
    SwapEndian( f );
}