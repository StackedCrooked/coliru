#include <iostream>

template<typename S> struct arg;

template<typename R, typename A>
struct arg <R(*)(A)> { using type = A; };

template<typename T>
T getObjectFromSomewhereElse() { return T{}; }

template <typename F>
void doSomethingWith(F func)
{
    using T = typename arg<F>::type;
   T obj = getObjectFromSomewhereElse<T>();
   func(obj);
}

void f(int x) { std::cout << x << std::endl; }

int main ()
{
	doSomethingWith(f);  // output 0
}
