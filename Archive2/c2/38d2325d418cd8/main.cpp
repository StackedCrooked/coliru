#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>

template <typename Container>
using less = std::less<
  typename std::decay<
    decltype(*std::declval<Container&>().begin())
  >::type
>;

namespace detail {
template<typename Container, typename Compare>
inline void sort(Container& container, Compare&& comp, ...) {
    using std::begin;
    using std::end;
    std::sort(begin(container), end(container), std::forward<Compare>(comp));
}

template<typename Container, typename Compare>
inline auto sort(Container& container, Compare&& comp, int) ->
  decltype(container.sort(std::forward<Compare>(comp))) {
    return container.sort(std::forward<Compare>(comp));
}
} // namespace detail

template<typename Container, typename Compare = less<Container>>
inline void sort(Container& container, Compare&& comp = {}) {
    detail::sort(container, std::forward<Compare>(comp), 0);
}

template <typename T>
void dump(const T& t) {
    std::cout << '{';
    auto first = true;
    for (auto const& i : t) {
        if (first) {
            first = false;
        } else {
            std::cout << ',';
        }
        std::cout << ' ' << i;
    }
    if (!first) {
        std::cout << ' ';
    }
    std::cout << "}\n";
}

int main() {
    std::array<int,5> arr = { 4, 3, 2, 1, 0 };
    std::list<int> list = { 4, 3, 2, 1, 0 };
    std::vector<int> vec = { 4, 3, 2, 1, 0 };

#define dump(container) do { std::cout << #container ": "; dump(container); } while(0)

    dump(arr);
    ::sort( arr );
    dump(arr);

    dump(list);
    ::sort( list );
    dump(list);

    dump(vec);
    ::sort( vec );
    dump(vec);
    
#undef dump
}
