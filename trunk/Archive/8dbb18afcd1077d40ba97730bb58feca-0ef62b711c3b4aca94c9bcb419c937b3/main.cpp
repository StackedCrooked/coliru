#include <tuple>
#include <array>
#include <string>
#include <type_traits>

int main(){
    using Scalar = int;
    using Array = std::array<double, 3>;
    using Tuple = std::tuple<char, float, std::string>;
    using result = decltype(std::tuple_cat(std::tuple<Scalar>(), std::declval<Array>(), std::declval<Tuple>()));
    using expected = std::tuple<int, double, double, double, char, float, std::string>;
    static_assert(std::is_same<result, expected>(), "...");
}