#include <iostream>

template <typename T>
struct get_arity : get_arity<decltype(&T::operator())> {};
template <typename R, typename... Args>
struct get_arity<R(*)(Args...)> : std::integral_constant<unsigned, sizeof...(Args)> {};
template <typename R, typename C, typename... Args>
struct get_arity<R(C::*)(Args...)> : std::integral_constant<unsigned, sizeof...(Args)> {};
template <typename R, typename C, typename... Args>
struct get_arity<R(C::*)(Args...) const> : std::integral_constant<unsigned, sizeof...(Args)> {};
// All combinations of variadic/non-variadic, cv-qualifiers and ref-qualifiers

template<typename TFunc>
void printArity(TFunc)
{
    std::cout << "arity: " << get_arity<TFunc>{} << std::endl;
}

void testFunc(int) { }

int main()
{
    printArity([](){}); // prints 0
    printArity([&](int, float){}); // prints 2
    printArity(testFunc); // prints 1
}