#include <functional>
#include <iostream>
#include <type_traits>

#define REM_CTOR(...) __VA_ARGS__

template <typename T, typename R>
using helper_ = std::conditional_t<std::is_rvalue_reference<R>{}, T&&, T&>;

#define SPEC(var, cv, ref) \
template <typename R, typename C, typename... Args> \
struct get_std_function<R(C::*)(Args... REM_CTOR var) cv ref > \
{using type = std::function<R(helper_<C cv, int ref>, Args... REM_CTOR var)>;};

#define REF(var, cv) SPEC(var, cv,) SPEC(var, cv, &) SPEC(var, cv, &&)

#define CV(var) REF(var,) REF(var, const) \
                REF(var, volatile) REF(var, const volatile)

template <typename> struct get_std_function;

CV(()) CV((,...))

template <typename T>
void print() {std::cout << __PRETTY_FUNCTION__ << '\n';}

int main()
{
    struct Test { void f(int) const volatile&; };
    
    print<get_std_function<decltype(&Test::f)>::type>();
}