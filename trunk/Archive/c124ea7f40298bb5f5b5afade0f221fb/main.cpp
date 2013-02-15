#include <type_traits>

template <typename>
struct always_false : std::false_type {};

template <typename T>
struct failure {
    static_assert(always_false<T>::value, "Requirements not met");
    using type = int;
};

template <typename T, bool Ok = T::value>
struct require { using type = int; };

template <typename T>
struct require<T, false> {
    using type = typename failure<T>::type;
};

template <typename T>
using Require = typename require<T>::type;

template <typename T, Require<std::is_integral<T>>...>
void f() {}

int main(){
    f<int>();
    f<double>();
}