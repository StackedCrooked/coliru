#include <forward_list>
#include <iterator>
#include <vector>
#include <iostream>

template<class Cont>
auto size_impl(const Cont& c, int) -> decltype(c.size()) {
    std::cout << "One\n";
    return c.size();
}

template<class Cont>
auto size_impl(const Cont& c, long) -> typename std::iterator_traits<decltype(std::begin(c))>::difference_type {
    std::cout << "Two\n";
    return std::distance(std::begin(c), std::end(c));
}

template<class Cont>
auto size(const Cont& c) -> decltype(size_impl(c, 0)) {
    return size_impl(c, 0);
}

int main() {
    std::forward_list<int> v = {1,2,3,4,5};
    std::cout << size(v) << '\n';
    std::vector<int> w = {1,2,3,4,5,6};
    std::cout << size(w) << '\n';
}