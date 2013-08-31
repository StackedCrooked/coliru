#include <vector>
#include <algorithm>
#include <iostream>
#include <type_traits>

struct sum_t {};

template<typename Pred>
using EnableIf = typename std::enable_if<Pred::value>::type;

template<typename T>
using Unqualified = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename Container, EnableIf<std::is_class<Unqualified<Container>>>...>
typename Unqualified<Container>::value_type operator|(const sum_t& sum_f, Container&& container) {
    return std::accumulate(std::begin(container),std::end(container),0);
}

int main() {
    std::vector<int> r = {1,2,3,4,5,6,7,8,9,10};
    auto result = sum_t{} | r;
    std::cout << result;
}