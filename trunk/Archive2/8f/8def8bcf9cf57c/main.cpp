#include <tuple>

template<typename T>
struct pop_front {
    using type = T;
};

template<typename T, typename... Args>
struct pop_front<std::tuple<T, Args...>> {
    using type = std::tuple<Args...>;
};

int main() {
    struct {} _ = pop_front<std::tuple<int, float, char>>::type{};
}