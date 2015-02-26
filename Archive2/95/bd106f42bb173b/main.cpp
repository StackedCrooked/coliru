#include <functional>
#include <type_traits>

struct fake_anything {};

auto fib = [](auto myself, int x) -> int{
  if(x < 2)
    return 1;
  return myself(x - 1) + myself(x - 2);
};

    template<class T>
    struct extract_signature;
    
    template<class T, class R, class FA, class...Args>
    struct extract_signature<R (T::*)(FA, Args...)> {
        static_assert(std::is_same<fake_anything, std::decay_t<FA>>::value, "Unexpected signature");
        using type = std::function<R(Args...)>;
    };
    
    template<class T, class R, class FA, class...Args>
    struct extract_signature<R (T::*)(FA, Args...) const> {
        static_assert(std::is_same<fake_anything, std::decay_t<FA>>::value, "Unexpected signature");
        using type = std::function<R(Args...)>;
    };
// other cv- and ref-qualifier versions omitted - not relevant to lambdas
// possibly other variations on the type of the first parameter, e.g., fake_anything &

template<class T>
using signature_t = typename extract_signature<decltype(&T::template operator()<fake_anything>)>::type;

int main() {
    static_assert(std::is_same<signature_t<decltype(fib)>, std::function<int(int)>>::value, "Oops");
}