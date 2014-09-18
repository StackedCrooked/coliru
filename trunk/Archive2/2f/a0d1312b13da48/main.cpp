#include <iostream>
#include <type_traits>
#include <cstddef>
#include <cassert>

template <typename... Types>
struct Foo;

template <typename T, typename... Types>
struct Foo<T, Types...> : Foo<Types...>
{
    Foo(T member, Types... others) : Foo<Types...>{others...}, m_member{member} {}
    T m_member;
};

template <typename T>
struct Foo<T>
{
    Foo(T member) : m_member{member} {}
    T m_member;
};

template <std::size_t N, typename T>
struct element;

template <typename T, typename... Types>
struct element<0, Foo<T, Types...>> 
{
    using type = T;
};

template <std::size_t N, typename T, typename... Types>
struct element<N, Foo<T, Types...>> 
{
    using type = typename element<N - 1, Foo<Types...>>::type;
};

template <std::size_t N, typename T, typename... Types>
auto get(Foo<T, Types...>& f)
    -> typename std::enable_if<N == 0, T&>::type
{
    return f.m_member;
}

template <std::size_t N, typename T, typename... Types>
auto get(Foo<T, Types...>& f)
    -> typename std::enable_if<N != 0, typename element<N, Foo<T, Types...>>::type&>::type
{
    Foo<Types...>& p = f;
    return get<N - 1>(p);
}

template <typename U, typename T, typename... Types>
auto get(Foo<T, Types...>& f)
    -> typename std::enable_if<std::is_same<T, U>::value, T&>::type
{
    return f.m_member;
}

template <typename U, typename T, typename... Types>
auto get(Foo<T, Types...>& f)
    -> typename std::enable_if<!std::is_same<T, U>::value, U&>::type
{
    Foo<Types...>& p = f;
    return get<U>(p);
}

int main()
{
    Foo<char, int, bool, double> a{ 'a', 42, true, 1.234 };
        
    std::cout << get<int>(a) << std::endl;
    std::cout << get<bool>(a) << std::endl;
    std::cout << get<double>(a) << std::endl;
    std::cout << get<3>(a) << std::endl;
    
    get<char>(a) = 'b';
    std::cout << get<0>(a) << std::endl;
}
