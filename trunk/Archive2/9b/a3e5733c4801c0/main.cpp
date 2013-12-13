#include <utility>
#include <type_traits>
 
 
template<typename T>
using NoRef = typename std::remove_reference<T>::type;
 
template<typename T>
using EnableIf = typename std::enable_if<T::value, void>::type;
 
//template<typename T, typename = void>
//struct is_callable_impl : std::is_function<T> {};
 
template<typename T>
struct is_callable_impl {
    using yes = char;
    using no = struct { char s[2]; };
 
    struct F { void operator()(); };
    struct Derived : T, F { };
    template<typename U, U> struct Check;
 
    template<typename V>
    static no test(Check<void (F::*)(), &V::operator()>*);
 
    template<typename>
    static yes test(...);
 
    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};
 
template<typename T>
struct Callable : std::integral_constant<bool, is_callable_impl<T>::value> {};
 
struct A {};
struct B { 
    void operator()(); 
};
 
struct C { 
    char operator()(int, int); 
};
struct D {
    template<typename T, typename U>
    void operator()(T, U);
    float operator()(int, char, double);
};
 
struct E {
    template<typename T>
    char operator()(T, double);
};
 
int main() {
    auto l = [] () { };
    static_assert(Callable<decltype(l)>::value, "...");
    static_assert(!Callable<A>::value, "...");
    static_assert(Callable<B>::value, "...");
    static_assert(Callable<C>::value, "...");
    static_assert(Callable<D>::value, "...");
    static_assert(Callable<E>::value, "...");
}