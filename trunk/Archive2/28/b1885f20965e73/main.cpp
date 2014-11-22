#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
 
template <typename F, typename T, std::size_t I, std::size_t Count>
typename std::enable_if<I >= Count>::type tuplecall__(T &&t, F &&f)
{
};

template <typename F, typename T, std::size_t I, std::size_t Count>
typename std::enable_if<I < Count>::type tuplecall__ (T &&t, F &&f)
{
    f(std::get<I>(t));
    tuplecall__<F, T, (I + 1), Count>(std::forward<T>(t), std::forward<F>(f));
};

template <typename T, typename F>
void tuple_foreach( T && t, F && f )
{
    tuplecall__<F, T, 0, std::tuple_size<typename std::remove_reference<T>::type>::value >(std::forward<T>(t), std::forward<F>(f));
};

int main()
{
    tuple_foreach(std::make_tuple("hello", "world"), [](auto &&t)
    {
        std::cout<<t;
    });
}