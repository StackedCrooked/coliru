#include <type_traits>

class Type1 {};
class Type2 {};
class Type3 {};
class Type4 {};

class TypeZ {};

// Implementation 1
template<typename T>
constexpr bool is_Type123_func()
{
  return std::is_same<T, Type1>() || std::is_same<T, Type2>() || std::is_same<T, Type3>();
}
template<typename T>
using Common_byfunc = typename std::conditional<is_Type123_func<T>(), TypeZ, T>::type;

static_assert(std::is_same<Common_byfunc<Type1>, TypeZ>(), "");
static_assert(std::is_same<Common_byfunc<Type2>, TypeZ>(), "");
static_assert(std::is_same<Common_byfunc<Type3>, TypeZ>(), "");
static_assert(!std::is_same<Common_byfunc<Type4>, TypeZ>(), "");

// Implementation 2
template<typename T>
struct is_Type123 : public std::conditional<std::is_same<T, Type1>() || std::is_same<T, Type2>() || std::is_same<T, Type3>(), std::true_type, std::false_type>::type {};
template<typename T>
using Common = typename std::conditional<is_Type123<T>::value, TypeZ, T>::type;

static_assert(std::is_same<Common<Type1>, TypeZ>(), "");
static_assert(std::is_same<Common<Type2>, TypeZ>(), "");
static_assert(std::is_same<Common<Type3>, TypeZ>(), "");
static_assert(!std::is_same<Common<Type4>, TypeZ>(), "");

int main(){}