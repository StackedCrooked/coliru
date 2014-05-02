template <typename... Ts>
struct Set {};

template <typename T, typename... Ts>
struct Tail1 { using type = Set<Ts...>; };

template <typename T, typename... Ts>
using Tail2 = Set<Ts...>;

template<typename... Ts>
using Test1 = typename Tail1<Ts...>::type;

template<typename... Ts>
using Test2 = Tail2<Ts...>;

Test1<int, char, double> t1;
Test2<int, char, double> t2;

int main() {}
