#include <initializer_list>

template<typename T>
class Deducer<T>;

template<typename T>
void func(const T& param)
{
    // Deducer<decltype(param)> d1;
    Deducer<T> d2;
}

auto autoReturningFunc() // should be explicitly specified as an std::initializer_list<int>
{
    return {1,2,3,4};
}

int main()
{
    func(28);
    auto x = {25};
    Deducer<decltype(x)> d1;
}