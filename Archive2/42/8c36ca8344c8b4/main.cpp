#include <iostream>

template<typename T> void doLambda(T&& mFn)
{
  std::forward<T>(mFn)(int{0});
}

template<typename T> void test(T&& mV)
{
    doLambda([&mV](auto mE)
    {
        std::forward<decltype(mV)>(mV);
    });
}

int main() { test(int{0}); return 0; }