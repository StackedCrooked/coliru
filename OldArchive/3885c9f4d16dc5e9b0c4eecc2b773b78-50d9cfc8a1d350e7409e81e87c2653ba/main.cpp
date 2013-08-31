#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

void plop(int a, int b, int c) {
    std::cout << a << " " << b << " " << c << std::endl;
}

template<typename T, typename... Queue>
struct caller {
template<typename... Converted>
static void call_func(Converted... args) {
    T t;
    caller<Queue...>::call_func(t, args...);
}
};

template<typename T>
struct caller<T> {
template<typename... Converted>
static void call_func(Converted... args) {
    T t;
    plop(t, args...);
}
};

int main()
{
    caller<int, int, int>::call_func();
}
