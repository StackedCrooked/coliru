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

template<typename T>
using UQ = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

static_assert(std::is_same<CT<T1>, UQ<T1>>::value, "T1");
static_assert(std::is_same<CT<T2>, UQ<T2>>::value, "T2");
static_assert(std::is_same<CT<T3>, UQ<T3>>::value, "T3");
static_assert(std::is_same<CT<T4>, UQ<T4>>::value, "T4");
static_assert(std::is_same<CT<T5>, UQ<T5>>::value, "T5");
static_assert(std::is_same<CT<T6>, UQ<T6>>::value, "T6");
static_assert(std::is_same<CT<T7>, UQ<T7>>::value, "T7");

int main(){}