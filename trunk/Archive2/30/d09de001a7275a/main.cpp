#include <iostream>
#include <functional>
#include <type_traits>

template<typename T, typename R>
struct match_struct
{
    T t;
    std::function<R(T)> f;
};

template<typename T, typename F,
    typename R = typename std::result_of<F(T)>::type>
match_struct<T, R> match(T t, F f)
{
    return match_struct<T, R>{t, f};
}

int main(int argc, char *argv[])
{
    auto m = match(10, [](int i){ return i;});
    return 0;
}
