#include <cstddef>
#include <type_traits>

struct Default {};

template<std::size_t Pos, bool UseDefault, typename... Ts>
struct At_;

template<std::size_t Pos, typename... Ts>
struct At_<Pos, true, Ts...> {
    using type = Default;
};

template<typename Head, typename... Tail>
struct At_<0, false, Head, Tail...> {
	using type = Head;
};

template<std::size_t Pos, typename Head, typename... Tail>
struct At_<Pos, false, Head, Tail...> {
	using type = typename At_<Pos - 1, false, Tail...>::type;
};

template<std::size_t Pos, typename... Ts>
using At = typename At_<Pos, sizeof...(Ts) <= Pos, Ts...>::type;

int main() {
    static_assert(std::is_same<At<0, int>, int>::value, "");
    static_assert(std::is_same<At<1, int>, Default>::value, "");
    
    static_assert(std::is_same<At<0>, Default>::value, "");
    static_assert(std::is_same<At<0, int, char>, int>::value, "");
    static_assert(std::is_same<At<1, int, char>, char>::value, "");
    static_assert(std::is_same<At<9001, int, char>, Default>::value, "");
}