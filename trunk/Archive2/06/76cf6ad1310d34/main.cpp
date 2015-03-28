#include <iostream>
#include <map>

template <typename Key, typename Value, typename... Ts>
struct helper;

template <typename Key, typename Value, typename First, typename Second, typename... Rest>
struct helper<Key, Value, First, Second, Rest...> {
    template <typename... Accum>
    static std::map<Key, Value>
    do_(First x, Second y, Rest... rest, Accum... accum) {
        return helper<Key, Value, Rest...>::do_(rest..., std::pair<First, Second>{x, y}, accum...);
    }
};

template <typename Key, typename Value>
struct helper<Key, Value> {
    template <typename... Accum>
    static std::map<Key, Value>
    do_(Accum... accum) {
        return {accum...};
    }
};

template <typename Key, typename Value, typename... Ts>
std::map<Key, Value>
make(Ts... ts) {
    return helper<Key, Value, Ts...>::do_(ts...);
}

int
main() {
    auto m = make<int, double>(
        1, 0.5,
        2, 1.0,
        3, 1.5,
        4, 2.0
    );
    
    for (auto p : m)
        std::cout << p.first << " -> " << p.second << '\n';
}
