#include <iostream>

// c++14 have it already for http://en.cppreference.com/w/cpp/utility/integer_sequence
namespace detail {
    template <int... Is> struct seq { };
    template <int N, int... Is> struct gen_seq : gen_seq<N - 1, N - 1, Is...> {  };
    template <int... Is> struct gen_seq<0, Is...> : seq<Is...> { };
}

// your slit with a debug log
template < char... val > struct slit {
    slit() {
        char vals[] = { val... };
        for( auto v : vals )
             std::cout << v << " ";
        std::cout << std::endl;
    }
};

constexpr int cstrlen( const char* str ) {
    const char* it { str };
    while( *it++ ){}
    return it-str;
}

#define EXPAND_STRING( type_name, str ) \
template <int... Is> slit< (str[Is])...> make_##type_name( detail::seq<Is...> ); \
using type_name = decltype( make_##type_name( detail::gen_seq<cstrlen(str)>{} ) );

using Manual = slit< 'b', 'a', 'z'>; 
EXPAND_STRING( MyFoo, "foo bar baz");
EXPAND_STRING( MyBar, "bla bli blo blu");

int main() {
    Manual{};
    MyFoo{};
    MyBar{};
}
