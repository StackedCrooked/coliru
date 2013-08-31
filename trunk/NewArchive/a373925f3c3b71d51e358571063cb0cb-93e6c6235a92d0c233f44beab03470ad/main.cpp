#include <utility>
#include <string>
#include <iostream>

template<typename Head, typename Tail> struct composer {
    Head head;
    Tail tail;
    composer(Head h, Tail t)
        : head(std::move(h)), tail(std::move(t)) {}
    template<typename... Args> auto operator()(Args&&... args) -> decltype(head(tail(std::forward<Args>(args)...))) {
        return head(tail(std::forward<Args>(args)...));
    }
};
template<typename Head, typename... Tail> struct composition_return_type {
    typedef composer<typename std::decay<Head>::type, typename composition_return_type<Tail...>::type> type;
};
template<typename Head> struct composition_return_type<Head> {
    typedef typename std::decay<Head>::type type;
};
template<typename Head> auto compose(Head&& head) -> typename std::decay<Head>::type {
    return std::forward<Head>(head);
}
template<typename Head, typename... Tail> auto compose(Head&& head, Tail&&... tail) -> typename composition_return_type<Head, Tail...>::type {
    return typename composition_return_type<Head, Tail...>::type(std::forward<Head>(head), compose(std::forward<Tail>(tail)...));
}

int main() {
    auto f = [] {
        return 1;
    };
    auto f2 = [](int x) {
        return x * 2;
    };
    auto f3 = [](int y) {
        return std::to_string(y);
    };
    auto f4 = [](std::string z) {
        return z + "Lol nubs";
    };
    std::cout << compose(f4, f3, f2, f)();
}