template <typename... Ts>
struct Set {};

template <typename T, typename... Ts>
struct TailHelper { using type = Set<Ts...>; };

template <typename... Ts>
using Tail = typename TailHelper<Ts...>::type;

template <typename T, typename TS>
struct MemberOf;

template <typename T, typename... Ts>
struct MemberOf<T, Set<T, Ts...>> {
    static constexpr bool value = true;
};

template <typename T>
struct MemberOf<T, Set<>> {
    static constexpr bool value = false;
};

template <typename T, typename... Ts>
struct MemberOf<T, Set<Ts...>> {
    static constexpr bool value = false || MemberOf<T, Tail<Ts...>>::value;
};

int main() {}
