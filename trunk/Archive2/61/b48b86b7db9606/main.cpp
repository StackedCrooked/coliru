#include <functional>
#include <iostream>

void foo(int a, long b, short c)
{
    std::cout << a << b << c << std::endl;
}

    template<int N>
    struct my_placeholder { static my_placeholder ph; };
    
    template<int N>
    my_placeholder<N> my_placeholder<N>::ph;
    
    namespace std {
        template<int N>
        struct is_placeholder<::my_placeholder<N>> : std::integral_constant<int, N> { };
    }

    void apply(std::function<void()> fun, int i)
    {
        fun();
    }
    template<class T, class... Ts>
    void apply(std::function<void(T, Ts...)> f, int i);
    
    template<class T, class... Ts, int... Is>
    void apply(std::function<void(T, Ts...)> f, int i, std::integer_sequence<int, Is...>)
    {
        std::function<void(Ts...)> g = std::bind(f, i, my_placeholder<Is + 1>::ph...);
        apply(g, ++i);
    }
    
    template<class T, class... Ts>
    void apply(std::function<void(T, Ts...)> f, int i) {
        apply(f, i, std::make_integer_sequence<int, sizeof...(Ts)>());
    }


int main()
{
    std::function<void(int, long, short)> bar1 = foo;
    apply(bar1, 0);

    return 0;
}