#include <utility>
#include <string>
#include <iostream>

template<typename T>
using Decay = typename std::decay<T>::type;

template<typename Head, typename Tail> 
struct composer {
    Head head;
    Tail tail;
    composer(Head h, Tail t)
        : head(std::move(h)), tail(std::move(t)) {}
    template<typename... Args> 
    auto operator()(Args&&... args) -> decltype(head(tail(std::forward<Args>(args)...))) {
        return head(tail(std::forward<Args>(args)...));
    }
};
template<typename Head, typename... Tail> 
struct composition_return_type {
    using type = composer<Decay<Head>, typename composition_return_type<Tail...>::type>;
};
template<typename Head> 
struct composition_return_type<Head> {
    using type = Decay<Head>;
};
template<typename Head> 
auto compose(Head&& head) -> Decay<Head> {
    return std::forward<Head>(head);
}
template<typename Head, typename... Tail> 
auto compose(Head&& head, Tail&&... tail) -> typename composition_return_type<Head, Tail...>::type {
    return typename composition_return_type<Head, Tail...>::type(std::forward<Head>(head), compose(std::forward<Tail>(tail)...));
}

int main() {
    auto f = [](int x, int y) {
        return x * y;
    };
    auto f2 = [](int x) {
        return x * 2;
    };
    auto f3 = [](int y) {
        return y * y;
    };
    auto f4 = [](int x) {
        return x + 11;
    };
    std::cout << compose(f4, f3, f2, f)(10, 11);
}