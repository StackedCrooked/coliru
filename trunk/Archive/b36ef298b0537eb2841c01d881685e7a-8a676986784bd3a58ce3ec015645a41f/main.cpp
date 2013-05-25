#include <type_traits>

using T1 = const int;
using T2 = volatile int;
using T3 = int &;
using T4 = const volatile int;
using T5 = const int &;
using T6 = volatile int &;
using T7 = const volatile int &;

template<typename T>
using CT = typename std::common_type<T>::type;

static_assert(std::is_same<CT<T1>, int>::value, "T1");
static_assert(std::is_same<CT<T2>, int>::value, "T2");
static_assert(std::is_same<CT<T3>, int>::value, "T3");
static_assert(std::is_same<CT<T4>, int>::value, "T4");
static_assert(std::is_same<CT<T5>, int>::value, "T5");
static_assert(std::is_same<CT<T6>, int>::value, "T6");
static_assert(std::is_same<CT<T7>, int>::value, "T7");

int main(){}