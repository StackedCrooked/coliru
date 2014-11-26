#include <iostream>
#include <type_traits>
#include <memory>
#include <tuple>
#include <utility>

namespace std {
    template <std::size_t I, class T>
    using tuple_element_t = typename tuple_element<I, T>::type;
}

template<class ArgTuple, class FunctionT, size_t... Is>
auto apply_impl(std::index_sequence<Is...>, FunctionT&& f, ArgTuple&& args) {
    return f(std::forward<std::tuple_element_t<Is, ArgTuple>>(std::get<Is>(args))...);
}

template<class ArgTuple, class FunctionT>
auto apply(FunctionT&& f, ArgTuple&& args) {
    return apply_impl(std::make_index_sequence<std::tuple_size<ArgTuple>::value>(), std::forward<FunctionT>(f), std::forward<ArgTuple>(args));
}

void another(std::unique_ptr<int>&& int_refref) {
    std::cout << "it works!\n";
}
void another2(int test) {
    std::cout << "test \n";
}

int main() {
    auto i = std::make_unique<int>(25);
    apply(another, std::make_tuple(std::move(i)));
    apply(another2, std::make_tuple(200));
    return 0;
}