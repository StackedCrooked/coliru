#include <utility>
#include <tuple>
#include <iostream>
#include <iomanip>

namespace detail
{   
    template<std::size_t... Is>
    struct index_sequence { };
    
    template<std::size_t N, std::size_t... Is>
    struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...> { };
    
    template<int... Is>
    struct make_index_sequence<0, Is...> : index_sequence<Is...> { };

    template<typename F, typename T, std::size_t... Is>
    void apply(F&& f, T&& t, index_sequence<Is...>)
    {
        (std::forward<F>(f))(std::get<Is>(t)...);
    }
}

template<typename F, typename T>
void apply(F&& f, T&& t)
{
    using tuple_type = std::remove_reference_t<T>;
    
    using indices = detail::make_index_sequence<std::tuple_size<tuple_type>::value>;
    
    detail::apply(std::forward<F>(f), std::forward<T>(t), indices{});
}

void foo(std::string const& s, int i, bool b)
{
    std::cout << std::boolalpha;
    
    std::cout << "foo(\"" << s << "\", " << i << ", " << b << ")";
}

int main()
{
    auto t = std::make_tuple("Hello", 42, true);
    
    apply(foo, t);
}