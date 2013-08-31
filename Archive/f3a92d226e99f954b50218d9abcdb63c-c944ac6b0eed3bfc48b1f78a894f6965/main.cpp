#include <array>
#include <tuple>
#include <string>

template <typename ArrayType, std::size_t ArraySize, typename... Fields>
struct ArrayTuple : ArrayTuple<ArrayType, ArraySize-1, ArrayType, Fields...> {};
template <typename ArrayType, typename... Fields>
struct ArrayTuple<ArrayType, 0, Fields...> {
    using type = std::tuple<Fields...>;
};

template <typename, typename, typename> class Test;

template <typename Scalar, typename ArrayType, std::size_t ArraySize, typename... Fields>
class Test<Scalar, std::array<ArrayType, ArraySize>, std::tuple<Fields...>> {
public:
    // Modified tuple_cat code from Xeo's comment:
    using Tuple = std::tuple<Fields...>;
    using Types = decltype(std::tuple_cat(std::tuple<Scalar>(), typename ArrayTuple<ArrayType, ArraySize>::type(), std::declval<Tuple>()));
};

int main() {
    using expected = std::tuple<int, double, double, double, char, float, std::string>;
    static_assert(typename std::is_same<Test<int, std::array<double, 3>, std::tuple<char, float, std::string>>::Types, expected>(), "...");
}
