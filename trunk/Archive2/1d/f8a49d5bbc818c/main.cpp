template<typename... Args>
struct types {};

namespace detail {
template<typename... RArgs>
types<RArgs...> reverse_types( types<RArgs...>, types<> ) {
    return types<RArgs...>();
}
template<typename Next, typename... Args, typename... RArgs>
auto reverse_types(types<RArgs...>, types<Next, Args...>) -> decltype(reverse_types(types<Next, RArgs...>(), types<Args...>())) {
	return reverse_types(types<RArgs..., Next>(), types<Args...>());
}
} // detail

template<typename... Args>
auto reverse_types() -> decltype(detail::reverse_types(types<>(), types<Args...>())) {
	return detail::reverse_types(types<>(), types<Args...>());
}

int main() {
    struct {} _ = reverse_types<char>();
    struct {} __ = reverse_types<char, int>();
    //struct {} ___ = reverse_types<char, int, float>();
    //struct {} ____ = reverse_types<char, int, float, double>();
}