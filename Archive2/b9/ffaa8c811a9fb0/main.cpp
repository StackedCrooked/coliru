#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <cstddef>
#include <tuple>

template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

template <int N>
struct placeholder {};

namespace std
{
    template <int N>
    struct is_placeholder<::placeholder<N>> : std::integral_constant<int, N> {};
}

template <std::size_t N, typename R, typename... Args, std::size_t... Before, std::size_t... After, typename Tuple = std::tuple<Args...>>
auto remove_param(index_sequence<Before...>, index_sequence<After...>)
    -> std::function<R(typename std::tuple_element<Before, Tuple>::type..., typename std::tuple_element<N + 1 + After, Tuple>::type...)>;

template <typename T, std::size_t N>
class LateBinding;

template <typename R, typename... Args, std::size_t N>
class LateBinding<R(Args...), N>
{    
public:
    explicit LateBinding(std::function<R(Args...)> f) : _f(f) {}

    LateBinding& operator=(std::function<R(Args...)> f)
    {
        _f = f;
        return *this;
    }

    template <typename T>
    auto operator()(T&& t)
        -> decltype(remove_param<N, R, Args...>(make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N - 1>{}))
    {
        return bindNth(std::forward<T>(t), make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N - 1>{});
    }   

private:
    template <typename T, std::size_t... Before, std::size_t... After>
    auto bindNth(T&& t, index_sequence<Before...>, index_sequence<After...>)
        -> decltype(remove_param<N, R, Args...>(make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N - 1>{}))
    {
        return std::bind(_f, placeholder<Before + 1>{}..., std::forward<T>(t), placeholder<N + 1 + After>{}...);
    }    

    std::function<R(Args...)> _f;
};

struct Class
{
    void method1(int i)
    {
        std::cout << "method1 " << i << std::endl;
    }
    
    void method2(int j)
    {
        std::cout << "method2 " << j << std::endl;
    }
    
    static int method3(int a, int b, int c)
    {
        return a + b + c;
    }
};

int main()
{    
    std::list<Class*> container(1, new Class);
    
    LateBinding<void(Class*, int), 1> functor{ &Class::method1 };        
    int param = 1;
    std::for_each(container.begin(), container.end(), functor(param));
         
    param = 2;
    std::for_each(container.begin(), container.end(), functor(param));
    
    functor = &Class::method2;    
    std::for_each(container.begin(), container.end(), functor(3));
        
    LateBinding<int(int, int, int), 2> functor2{ &Class::method3 };
    std::cout << functor2(2)(1, 3) << std::endl;
}
