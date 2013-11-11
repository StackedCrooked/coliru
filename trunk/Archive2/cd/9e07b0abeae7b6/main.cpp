#include <type_traits>

template<typename... Ts>
struct List{
    typedef List<Ts...> Type;
    enum {
        size = sizeof...(Ts)
    };
};

template<int I>
using IntType = std::integral_constant<int, I>;

namespace Detail {
    template <typename T, typename U>
    struct Max : IntType<(U::value > T::value) ? U::value : T::value> {};
    template<int I, typename T, typename... Ts>
    struct FindLast : IntType<-1>{};
    template<int I, typename T, typename U, typename... Ts>
    struct FindLast<I, T, U, Ts...> : FindLast<I + 1, T, Ts...>{};
    template<int I, typename T, typename... Ts>
    struct FindLast<I, T, T, Ts...> : Max<IntType<I>, FindLast<I + 1, T, Ts...>> {};
}

template<typename T, typename U>
struct FindLast;
template<typename T, typename... Ts>
struct FindLast<T, List<Ts...>> : Detail::FindLast<0, T, Ts...>{};

static_assert(FindLast<long, List<long, char, char, long, void*>>() == 3, "BOOM!");
