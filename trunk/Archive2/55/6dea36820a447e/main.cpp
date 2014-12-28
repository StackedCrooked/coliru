#include <iostream>
#include <future>

namespace detail {
template<typename Future, typename Worker>
inline auto do_work(Future& f, Worker& w) -> decltype(w(f.get())) {
    return w(f.get());
}

template<typename Future, typename Worker>
inline auto do_work(Future& f, Worker& w) -> decltype(w()) {
    f.wait();
    return w();
}

template<typename L, typename T>
struct rebind {};

template<template<typename...> class L, typename T, typename U, typename... Args>
struct rebind<L<T, Args...>, U> {
    using type = L<U, Args...>;
};
} // detail

template<typename Future, typename Worker>
auto then(Future f, Worker w) -> typename detail::rebind<Future, decltype(detail::do_work(f, w))>::type {
    return std::async(std::launch::async, [](Future fut, Worker work) {
        return detail::do_work(fut, work);
    }, std::move(f), std::move(w));
}

int multiply_five(int x) {
    return x * 5;
}

int add_ten(int x) {
    return x + 10;
}

int get_number() {
    return 10;
}

int main() {
    auto&& f = std::async(std::launch::async, get_number);
    auto&& f2 = then(std::move(f), add_ten);
    auto&& f3 = then(std::move(f2), multiply_five);
    std::cout << "Hello World\n";
    std::cout << f3.get() << '\n';
}
