#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

namespace detail {
using std::begin;
using std::end;

template<typename Container, typename Compare>
inline void sort_(Container& container, Compare&& comp, ...) {
    std::sort(begin(container), end(container), std::forward<Compare>(comp));
}

template<typename Container, typename Compare>
inline auto sort_(Container& container, Compare&& comp, int) ->
  decltype(container.sort(std::forward<Compare>(comp))) {
    return container.sort(std::forward<Compare>(comp));
}

template<typename Container, typename Compare = std::less<
  typename std::decay<
    decltype(*begin(std::declval<Container&>()))
  >::type
>>
inline void sort(Container& container, Compare&& comp = {}) {
    sort_(container, std::forward<Compare>(comp), 0);
}
} // namespace detail
using detail::sort;


#include <array>
#include <list>
#include <vector>
#include <iostream>

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
    int raw_array[] = { 4, 3, 2, 1, 0 };

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

    dump(raw_array);
    ::sort(raw_array);
    dump(raw_array);
    
#undef dump
}
