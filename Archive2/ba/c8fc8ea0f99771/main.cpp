#include <array>
#include <iostream>
#include <tuple>
#include <utility>

template<std::size_t N, typename T, typename F, std::size_t... Indices>
auto apply_from_array_impl(F&& func, T (&arr)[N], std::index_sequence<Indices...>)
    -> decltype(auto)
{
    return std::forward<F>(func)(arr[Indices]...);
}

template<std::size_t N, typename T, typename F>
auto apply_from_array(F&& func, T (&arr)[N])
    -> decltype(auto)
{
    using Indices = std::make_index_sequence<N>;
    return apply_from_array_impl(std::forward<F>(func), arr, Indices());
}

struct Value
{
    Value() = delete;
    
    Value(int val): val{val} {}
    
    int val;
};

Value foo(Value a, Value b, Value c)
{
    return { a.val + b.val + c.val };
}

int main()
{
    Value arr[] = { 1, 2, 3 };
    
    std::cout << apply_from_array(foo, arr).val;
}
