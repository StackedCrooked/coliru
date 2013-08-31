#include <type_traits>

template<class D, class T>
using First = D;

template<bool B>
using Bool = std::integral_constant<bool, B>;
using True = Bool<true>;
using False = Bool<false>;

constexpr True true_{};
constexpr False false_{};

template<class... Depends>
struct build_and{
    static constexpr bool eval(First<True, Depends>...){ return true; }
    static constexpr bool eval(...){ return false; }
};

int main()
{
    static_assert(build_and<int, int, int, int>::eval(true_, true_, true_, true_), "True");
    static_assert(!build_and<int, int, int, int>::eval(true_, true_, false_, true_), "False");
}