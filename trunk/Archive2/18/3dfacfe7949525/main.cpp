#include <cstdint>
#include <iostream>
#include <utility>

template <std::uint64_t I>
struct yeller {
    yeller() { 
        std::cout << I << '\n'; 
    }
};

template <typename T>
struct yell_sequence;

template <std::uint64_t... Seq>
struct yell_sequence<std::integer_sequence<std::uint64_t, Seq...>> 
    : yeller<Seq>...
{ };
    
int
main() {
    yell_sequence<std::make_integer_sequence<std::uint64_t, 10>> y;
}
