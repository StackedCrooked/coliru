#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <memory>
#include <initializer_list>

namespace detail {

template<class T> struct is_contiguous_range : std::false_type{};
template<class T, size_t N> struct is_contiguous_range<T[N]> : std::true_type{};
template<class T, size_t N> struct is_contiguous_range<std::array<T, N>> : std::true_type{};
template<class T, class Alloc> struct is_contiguous_range<std::vector<T, Alloc>> : std::true_type{};
 // vector<bool> is broken.
template<class Alloc> struct is_contiguous_range<std::vector<bool, Alloc>> : std::false_type{};


template<class T> struct value_type { typedef typename T::value_type type; };
template<class T, size_t N> struct value_type<T[N]> { typedef T type; };

template<class T> auto data(T const& x) -> decltype(std::addressof(*std::begin(x))) { return std::addressof(*std::begin(x)); }
template<class T> auto size(T const& x) -> decltype(std::end(x) - std::begin(x)) { return std::end(x) - std::begin(x); }

}



template<
    typename Container,
    class = typename std::enable_if<detail::is_contiguous_range<Container>::value>,
    class = typename std::enable_if<
                                    std::is_pod<
                                                typename detail::value_type<Container>::type>::value>
                                                                                                    
>
void data(Container const& v) {    
    std::cout << detail::data(v) << " ";
    std::cout << detail::data(v) + detail::size(v) << " ";
}


int main() {
    std::vector<int> v { 1,2,3 };
    std::array<int,3> a { 4, 5, 6 };
    int c[] = { 7, 8, 9 };
    int d[3] = { 10, 11, 12 };

    data(v);
    data(a);
    data(c);
    data(d);
}

