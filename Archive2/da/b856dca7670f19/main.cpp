#include <iostream>
#include <type_traits>
#include <memory>
#include <tuple>
#include <utility>

template<class ArgTuple, class FunctionT, size_t... Is>
auto apply_impl(std::index_sequence<Is...>, FunctionT&& f, ArgTuple&& args) {
    return f(std::forward(std::get<Is>(args))...);
}

template<class ArgTuple, class FunctionT>
auto apply(FunctionT&& f, ArgTuple&& args) {
    return apply_impl(std::make_index_sequence<std::tuple_size<ArgTuple>::value>(), f, std::forward(args));
}

void another(std::unique_ptr<int>&& int_refref) {
}

int main() {
    auto i = std::make_unique<int>(25);
    apply(another,
        std::forward_as_tuple(
            std::move(i)
        )
    );
    return 0;
}