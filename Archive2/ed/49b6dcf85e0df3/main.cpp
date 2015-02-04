#include <iostream>

// Rotating a pack N to the left.
template <int, typename> struct Rotate;

template <template <typename...> class P, typename First, typename... Rest>
struct Rotate<0, P<First, Rest...>> {
    using type = P<First, Rest...>;
};

template <int N, int K>
struct PositiveModulo : std::integral_constant<int, (N % K + K) % K> {};

template <int N, template <typename...> class P, typename First, typename... Rest>
struct Rotate<N, P<First, Rest...>> :
    Rotate<PositiveModulo<N-1, sizeof...(Rest)+1>::value, P<Rest..., First>> {};

enum {Rot, Rev, /* ... */};  // enum values for each type of pack transformation.

template <typename, int, int...> struct PackTransformation;

// Specializations of PackTransformation to carry out each type of pack transformation.
template <template <typename...> class P, int N, typename... Types>
struct PackTransformation<P<Types...>, Rot, N> {
    using type = typename Rotate<N, P<Types...>>::type;
};
// Similarly struct PackTransformation<P<Types...>, Rev> will reverse P<Types...>, etc...

// Attempt to have PackTransformation applied to each inner pack in a nested pack:
template <typename T, int, int...> struct TransformNestedPack {
    using type = T;
};

template <template <typename...> class P, typename... Types, int N, int... Parameters>
struct TransformNestedPack<P<Types...>, N, Parameters...> : PackTransformation<P<typename TransformNestedPack<Types, N, Parameters...>::type...>, N, Parameters...> {};

template <typename...> struct Pack {};

template<class> class TD;

int main() {
    using NestedPack = Pack<Pack<int, Pack<double, char, long>>, char, long, short>;
    PackTransformation<NestedPack, Rot, 1>::type a;  // Rotates NestedPack to the left by 2, but not the inner pack.
    std::cout << std::boolalpha << std::is_same< decltype(a),
        Pack<char, long, short, Pack<int, Pack<double, char, long>>>
    >::value << std::endl;  // true

    TransformNestedPack<NestedPack, Rot, 1>::type b;
    std::cout << std::is_same< decltype(b),
        Pack<char, long, short, Pack<Pack<char, long, double>, int>>
    >::value << std::endl;  // true
    // The above currently works only if there is one nested pack and that nested pack is the first type.
}