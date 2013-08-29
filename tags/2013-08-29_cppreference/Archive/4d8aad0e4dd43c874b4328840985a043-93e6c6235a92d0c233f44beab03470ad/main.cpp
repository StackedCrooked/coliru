#include <utility>
#include <string>
#include <iostream>

template<typename Head, typename Tail> struct composer {
    Head head;
    Tail tail;
    composer(Head h, Tail t)
        : head(std::move(h)), tail(std::move(t)) {}
    template<typename... Args> auto operator()(Args&&... args) -> decltype(h(t(std::forward<Args>(args)...))) {
        return h(t(std::forward<Args>(args)...));
    }
};
template<typename Head, typename... Tail> auto compose(Head&& head, Tail&&... tail) -> composer<typename std::decay<Head>::type, decltype(compose(std::forward<Tail>(tail)...))> {
    return composer<typename std::decay<Head>::type, decltype(compose(std::forward<Tail>(tail)...))>(std::forward<Head>(head), compose(std::forward<Tail>(tail)...));
}
template<typename Head> auto compose(Head&& head) -> typename std::decay<Head>::type {
    return std::forward<Head>(head);
}

int main() {
    auto f = [] {
        return 1;
    };
    auto f2 = [](int x) {
        return x * 2;
    };
    auto f3 = [](int y) {
        return std::to_string(z);
    };
    auto f4 = [](std::string z) {
        return z + "Lol nubs";
    };
    std::cout << compose(f4, f3, f2, f)();
}