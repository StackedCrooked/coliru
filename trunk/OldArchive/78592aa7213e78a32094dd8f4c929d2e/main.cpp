#include <type_traits>

template <typename Condition>
using EnableIf = typename std::enable_if<Condition::value>::type;

template<
    typename T,
    EnableIf<std::is_arithmetic<T>>...
> struct S{};

int main() {
   S<int> s; //compiles
   //S<int*> t; //doesn't compile
}