#include <functional>
#include <iostream>

template <class T, class... Args>
class VariadicTest {
public:
    VariadicTest(const T& func, Args... args) : func(args...) {};
private:
    std::function<decltype(std::declval<T>()(std::declval<Args>()...))(Args...)> func;
};

int main()
{
    
}