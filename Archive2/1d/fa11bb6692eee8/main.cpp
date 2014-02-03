#include <string>
#include <iostream>

template <typename F, typename...Ts>
void fun(F f, Ts&&...args)
{
    int dummy[] = {0, (f(std::forward<Ts>(args)), 0)...};
    static_cast<void>(dummy); // remove warning for unused variable
}

void foo(std::string value) { std::cout << 's' << value << " "; }
void foo(int value) { std::cout << 'i' << value << " "; }

int main()
{
    fun(foo, 42, "abc", 3.5);
}
