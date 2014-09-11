#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <type_traits>

template <std::size_t N>
struct int_t;

template <>
struct int_t<64> { using type = long; };

struct big_int { };

namespace detail {
    template <std::size_t N>
    class has_int {
        using yes = char[1];
        using no  = char[2];
        
        template <std::size_t M>
        static yes&
        test(typename int_t<M>::type*);
        
        template <std::size_t>
        static no&
        test(...);
        
    public:
        static constexpr bool value = 
            sizeof(test<N>(nullptr)) == sizeof(yes);
    };
}

template <std::size_t N, bool = detail::has_int<N>::value>
struct choose {
    using type = big_int;
};

template <std::size_t N>
struct choose<N, true> {
    using type = typename int_t<N>::type;
};

int
main() {
    using A = choose<128>::type;
    using B = choose<64>::type;
    
    std::cout << typeid(A).name() << " " << typeid(B).name() << '\n';
}
    