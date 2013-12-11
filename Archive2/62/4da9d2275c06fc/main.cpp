#include <iostream>
#include <string>
#include <tuple>
#include <vector>

template<class U, class V>
constexpr bool has_common_type_f_impl(typename std::common_type<U, V>::type*) { return true; }
template<class U, class V>
constexpr bool has_common_type_f_impl(...) { return false; }

template<class U, class V>
constexpr bool has_common_type_f() { return has_common_type_f_impl<U,V>(0); }

template<class ...Types>
struct has_common_type;

template<>
struct has_common_type<> { enum{ value = true }; };
template<class T>
struct has_common_type<T> { enum{ value = true }; };
template<class T>
struct has_common_type<T,T> { enum{ value = true }; };
template<class T, class U>
struct has_common_type<T, U> { enum{ value = has_common_type_f<T,U>() }; };
template<class T, class U, class ...Rest>
struct has_common_type<T, U, Rest...> { 
    enum{ 
        value = has_common_type<T,U>::value 
             && has_common_type<T, Rest...>::value
             && has_common_type<U, Rest...>::value
    }; 
};

static_assert(has_common_type<int>::value, "Sanity check");
static_assert(has_common_type<int, int>::value, "Sanity check");
static_assert(has_common_type<int, double>::value, "Sanity check");
static_assert(has_common_type<char, int, float, double>::value, "Sanity check");

int main()
{
}
