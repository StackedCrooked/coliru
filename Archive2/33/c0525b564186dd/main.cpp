#include <iostream>
#include <type_traits>

using namespace std;

// utility class, don't consider
template <class T, T... I> struct integer_sequence
{
    template <T N> using append = integer_sequence<T, I..., N>;
    static std::size_t size () { return sizeof...(I); }
    using next = append<sizeof...(I)>;
    using type = T;
};
 
template <class T, T Index, std::size_t N>
struct sequence_generator 
{
    using type = typename sequence_generator<T, Index - 1, N - 1>::type::next;
};
 
template <class T, T Index>
struct sequence_generator<T, Index, 0ul> { using type = integer_sequence<T>; };
 
template <std::size_t... I>
using index_sequence = integer_sequence<std::size_t, I...>;
 
template <class T, T N>
using make_integer_sequence = typename sequence_generator<T, N, N>::type;
 
template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template<typename... T>
struct remove_first_index;

template<std::size_t... I>
struct remove_first_index<index_sequence<I...>>
{
};


int main() {
    make_index_sequence<5> foo;
	remove_first_index<decltype(foo)> foo2;
    
	return 0;
}