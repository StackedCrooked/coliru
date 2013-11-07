#include <type_traits>

template<class T, class = void>
struct trait : std::false_type{};
template<class T>
struct trait<T, decltype(std::declval<T>().foo, void())> : std::true_type{};

struct X{ int foo; };
struct Y{};

static_assert(trait<X>(), "X");
static_assert(not trait<Y>(), "Y");

int main(){}