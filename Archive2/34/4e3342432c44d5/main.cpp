#include <cstddef>
#include <iostream>
#include <iterator>
#include <array>
#include <type_traits>

namespace patch {
    /// A type that represents a parameter pack of zero or more integers.
    template<typename T, T... I>
    struct integer_sequence {
        static_assert( std::is_integral<T>::value, "Integral type" );
    
        using type = T;
    
        static constexpr T size = sizeof...(I);
    
        /// Generate an integer_sequence with an additional element.
        template<T N>
        using append = integer_sequence<T, I..., N>;
        using next = append<size>;
    };
    
    template<typename T, T... I>
    constexpr T integer_sequence<T, I...>::size;
    
    template<std::size_t... I>
    using index_sequence = integer_sequence<std::size_t, I...>;
    
    namespace detail {
        // Metafunction that generates an integer_sequence of T containing [0, N)
        template<typename T, T Nt, std::size_t N>
        struct iota {
            static_assert( Nt >= 0, "N cannot be negative" );
            using type = typename iota<T, Nt-1, N-1>::type::next;
        };
        
        // Terminal case of the recursive metafunction.
        template<typename T, T Nt>
        struct iota<T, Nt, 0ul> {
            using type = integer_sequence<T>;
        };
    }
    
    
    // make_integer_sequence<T, N> is an alias for integer_sequence<T, 0,...N-1>
    template<typename T, T N>
    using make_integer_sequence = typename detail::iota<T, N, N>::type;
    
    template<int N>
    using make_index_sequence = make_integer_sequence<std::size_t, N>;
    
    // index_sequence_for<A, B, C> is an alias for index_sequence<0, 1, 2>
    template<typename... Args>
    using index_sequence_for = make_index_sequence<sizeof...(Args)>;

}  // namespace patch

template<class Function, std::size_t... Indices>
constexpr auto make_array_helper(Function f, patch::index_sequence<Indices...>) 
    -> std::array<typename std::result_of<Function(std::size_t)>::type, sizeof...(Indices)> {
    return {{ f(Indices)... }};
}

template<int N, class Function>
constexpr auto make_array(Function f)
    -> std::array<typename std::result_of<Function(std::size_t)>::type, N> {
    return make_array_helper(f, patch::make_index_sequence<N>{});    
}

constexpr double init_list(const int n) { 
    return n * n * n; 
}

int main() {
    constexpr auto N = 10;
    constexpr auto a = make_array<N>(init_list);
    
    std::copy(std::begin(a), std::end(a), std::ostream_iterator<double>(std::cout, ", ")); 
}