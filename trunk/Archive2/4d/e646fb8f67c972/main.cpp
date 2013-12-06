#include <type_traits>

class Type1 {};
class Type2 {};
class Type3 {};
class Type4 {};

class TypeZ {};

template<typename T>
struct Common_helper : std::conditional<std::is_same<T, Type1>() || std::is_same<T, Type2>() || std::is_same<T, Type3>(), TypeZ, T> {};

template<typename T>
using Common = typename Common_helper<T>::type;

static_assert(std::is_same<Common<Type1>, TypeZ>(), "");
static_assert(std::is_same<Common<Type2>, TypeZ>(), "");
static_assert(std::is_same<Common<Type3>, TypeZ>(), "");
static_assert(!std::is_same<Common<Type4>, TypeZ>(), "");

int main(){}