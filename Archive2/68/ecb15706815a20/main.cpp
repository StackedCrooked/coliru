#include <limits>
#include <type_traits>
#include <iterator>

template <int i> struct rank : rank<i - 1> {};

template <>	struct rank<0> {};

using call_ranked = rank<256>;

template <typename It>
auto distance_ranked(rank<0>, It it, It end) -> std::size_t {
    std::size_t size{};
    while (it != end) {
        ++it;
        ++size;
    }
    return size;
}

template <typename It>
auto distance_ranked(rank<1>, It begin, It end)
     -> typename std::enable_if<std::is_same<typename std::iterator_traits<It>::iterator_category,
                                             std::random_access_iterator_tag>{}, std::size_t>::type {
    return end - begin;
}

// Delegating function template:
template <typename... Args>
auto distance(Args&&... args)
    -> decltype(distance_ranked(call_ranked(), std::forward<Args>(args)...)) {
    return      distance_ranked(call_ranked(), std::forward<Args>(args)...);
}

#include <iostream>

int main()
{
    int *a = nullptr, *b = nullptr;
    std::cout << distance(a, b);
}