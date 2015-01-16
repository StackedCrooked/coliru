#include <iostream>

// c++14 has it http://en.cppreference.com/w/cpp/utility/integer_sequence
namespace detail {
    template <int... Is> struct seq { };
    template <int N, int... Is> struct gen_seq : gen_seq<N - 1, N - 1, Is...> {  };
    template <int... Is> struct gen_seq<0, Is...> : seq<Is...> { };
}


constexpr size_t operator"" abclenlen ( const char*, size_t len ){ return len; }
template < char... val > struct slit {};

#define EXPAND_STRING( type_name, str ) \
template <int... Is> slit< str[Is]...> make_##type_name( detail::seq<Is...> ); \
using type_name = decltype( make_##type_name( detail::gen_seq<str##abclen>{} ) );

using Manual = slit< 'b', 'a', 'z'>; 
EXPAND_STRING( MyFoo, "foo bar baz")
EXPAND_STRING( MyBar, "bla bli blo blu")

inline std::ostream& operator<<( std::ostream& os, slit<> ) { return os; }
template < char first, char... chars >/
std::ostream& operator<<( std::ostream& os, slit<first,chars...> ) {
    return os << first << " " << slit<chars...>{};
}

int main() {
    std::cout << Manual{} << "\n";
    std::cout << MyFoo{} << "\n";
    std::cout << MyBar{} << "\n";
}