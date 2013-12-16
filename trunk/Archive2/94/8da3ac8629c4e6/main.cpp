#include <type_traits>

class Type1 {};
class Type2 {};
class Type3 {};
class Type4 {};

class TypeZ {};

template<typename T>
struct is_Type123 : public std::conditional<std::is_same<T, Type1>() || std::is_same<T, Type2>() || std::is_same<T, Type3>(), std::false_type, std::true_type>::type {};

template<typename T>
using Common = typename std::conditional<is_Type123<T>::value, T, TypeZ>::type;

static_assert(std::is_same<Common<Type1>, TypeZ>(), "");
static_assert(std::is_same<Common<Type2>, TypeZ>(), "");
static_assert(std::is_same<Common<Type3>, TypeZ>(), "");
static_assert(!std::is_same<Common<Type4>, TypeZ>(), "");

int main(){}