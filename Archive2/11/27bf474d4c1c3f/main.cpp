#include <tuple>

template <class Result, class Function, class... Types>
Result f(Function func, Types... values)
{
    return std::get<0>(std::make_tuple(func(values)...));
}

template <class... Types>
int g(const Types... values)
{
    auto dummy = [](int n){return n;};
    return std::get<0>(std::make_tuple(f<Types>(dummy, values)...));
}

int main()
{
    return g(42);
}
