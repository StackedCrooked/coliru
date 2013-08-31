#include <vector>
#include <algorithm>
#include <iostream>
#include <type_traits>

struct sum_t {};

template<typename Container, typename std::enable_if<std::is_class<typename std::decay<Container>::type>::value, int>::type =  0>
typename std::decay<Container>::type::value_type operator|(const sum_t& sum_f, Container&& container) {
    return std::accumulate(std::begin(container),std::end(container),0);
}

int main() {
    std::vector<int> r = {1,2,3,4,5,6,7,8,9,10};
    auto result = sum_t{} | r;
    std::cout << result;
}