#include <chrono>
#include <iostream>

template <typename T, class Rep, class Period>
constexpr T(*DurationCast)(const std::chrono::duration<Rep, Period>&) = &std::chrono::duration_cast<T, Rep, Period>;

template <typename T>
void foo()
{
    std::cout << "foo!" << (T)3.14f << std::endl;
}

template <typename T>
constexpr void(*foo_alias)() = &foo<T>;

int main()
{
    std::chrono::seconds s(1);
    std::chrono::milliseconds ms = DurationCast<std::chrono::milliseconds, float, std::ratio<1>>(s);    
    std::cout << "ms: " << ms.count() << std::endl;
    
    foo_alias<int>();
    foo_alias<float>();
}
