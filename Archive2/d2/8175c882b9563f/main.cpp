#include <initializer_list>
#include <iostream>
#include <typeinfo>
#include <functional>

template <typename Tp, typename Tp2, typename... Args>
auto operator+(std::function<Tp(Args...)> a, std::function<Tp2(Args...)> b) {
    return [=](Args... args) -> std::pair<Tp, Tp2> {
        return std::pair<Tp, Tp2>(a(args...), b(args...));
    };
}

template <typename Tp2, typename... Args>
auto operator+(std::function<void(Args...)> a, std::function<Tp2(Args...)> b) {
    return [=](Args... args) -> Tp2 {
        a(args...);
        return b(args...);
    };
}

template <typename Tp, typename... Args>
auto operator+(std::function<Tp(Args...)> a, std::function<void(Args...)> b) {
    return [=](Args... args) -> Tp {
        auto st = a(args...);
        b(args...);
        return st;
    };
}

template <typename... Args>
auto operator+(std::function<void(Args...)> a, std::function<void(Args...)> b) {
    return [=](Args... args) {
        a(args...);
        b(args...);
    };
}

int main() {
    std::function<std::string(int)> a = [](int x) {
        return std::to_string(x);
    };
    
    std::function<float(int)> b = [](int y) {
        return (float)y;
    };
    
    std::cout << (a + b)(1).first << std::endl;
}