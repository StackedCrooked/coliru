#include <tuple>

template<typename... Ts>
struct reverse_tuple;

template <>
struct reverse_tuple<std::tuple<>> {
    using type = std::tuple<>;
};

template <typename T, typename... Ts>
struct reverse_tuple<std::tuple<T, Ts...>> {
  using head = std::tuple<T>;
  using tail = typename reverse_tuple<std::tuple<Ts...>>::type;
  using type = decltype(std::tuple_cat(std::declval<tail>(), std::declval<head>()));
};

int main() {
    struct {} _ = typename reverse_tuple<std::tuple<int, char, bool>>::type{};
}