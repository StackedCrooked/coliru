#include <type_traits>

template<typename... Ts>
struct largest;

template<typename T>
struct largest<T> {
    using type = T;
};

template<typename T, typename U>
struct largest<T, U> {
    using type = typename std::conditional<sizeof(T) >= sizeof(U), T, U>::type;
};

template<typename Head, typename Head2, typename... Tail>
struct largest<Head, Head2, Tail...> {
    using type = typename largest<typename largest<Head, Head2>::type, Tail...>::type;
};

static_assert(std::is_same<largest<char, double, short>::type, double>::value, "meh");

int main() {}