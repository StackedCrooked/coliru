#include <utility>
#include <type_traits>

template<typename... Args>
struct Or : std::false_type {};

template<typename T, typename... Args>
struct Or<T, Args...> : std::conditional<T::value, std::true_type, Or<Args...>>::type {};

template<typename Test, typename... Args>
using TraitOf = decltype(Test::template test<Args...>(0));

struct is_class_callable {
    template<typename T>
    static auto test(int) -> decltype(&T::operator(), std::true_type{}) {}
    template<typename>
    static std::false_type test(...);
};

template<typename T>
struct Callable : Or<std::is_function<T>, TraitOf<is_class_callable, T>> {};

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
    static_assert(!Callable<int>::value, "...");
    static_assert(Callable<void()>::value, "...");
    auto l = [] () { };
    static_assert(Callable<decltype(l)>::value, "...");
    static_assert(!Callable<A>::value, "...");
    static_assert(Callable<B>::value, "...");
    static_assert(Callable<C>::value, "...");
    static_assert(Callable<D>::value, "...");
    static_assert(Callable<E>::value, "...");
}