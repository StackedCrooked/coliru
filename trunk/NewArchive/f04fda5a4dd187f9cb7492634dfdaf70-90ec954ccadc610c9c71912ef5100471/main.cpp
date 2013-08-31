// --- proof of concept ---
struct brick {
    brick(int) {}
    brick(brick const&) = delete;
    brick(brick&&) = delete;
    brick& operator=(brick const&) = delete;
    brick& operator=(brick&&) = delete;
};

brick make_brick(int n) {
    return { n };
}

void poc() {
    auto&& b = make_brick(42);
    (void)b;
}

// --- implementation ---
#include <initializer_list>
#include <type_traits>
#include <utility>

template <typename... T>
using CommonType = typename std::common_type<T...>::type;

template <typename T>
using Decay = typename std::decay<T>::type;

template <typename... T,
          typename Common = CommonType<Decay<T>...>>
std::initializer_list<Common> list(T&&... t) {
    return { std::forward<T>(t)... };
}

template <typename T>
void f(T) {}

int main() {
    poc();
    f(list(1, 2, 3, 4, 5));
}