#include <iostream>
#include <type_traits>
#include <algorithm>
#include <vector>

namespace std {
template <typename T>
inline
auto rbegin(const T& t) {
    return static_cast<std::reverse_iterator< typename T::iterator>>({ std::end(t) });
}

}


int main() {
    std::vector<int> x = { 2, 3, 1 };
    std::rbegin(x);
}