#include <tuple>

template <class Result, class Function, class... Types>
Result f(Function func, Types... values)
{
    return std::get<0>(std::make_tuple(func(values)...));
}

// requires C++1y
auto func() { return [](int n){return n;}; }

template <class... Types>
int g(const Types... values)
{
    return std::get<0>(std::make_tuple(f<Types>(func(), values)...));
}

int main()
{
    return g(42);
}
