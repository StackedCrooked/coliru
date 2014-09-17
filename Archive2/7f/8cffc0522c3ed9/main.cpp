#include <iostream>
#include <type_traits>
#include <cstddef>

template<typename... Types>
struct Foo;

template <typename T, typename... Types>
struct Foo<T, Types...> : Foo<Types...>
{
    // bring get() member functions from parent class into current scope
    using Foo<Types...>::get;
    
    Foo(T member, Types... others) : Foo<Types...>{others...}, m_member{member} {}
    
    template <typename F>
    auto get() -> typename std::enable_if<std::is_same<F,T>::value, T>::type
    {
        return m_member;
    }
    
    template <std::size_t N>
    auto get() -> typename std::enable_if<N == sizeof...(Types), T>::type
    {
        return m_member;
    }
    
private:
    T m_member;
};

template <typename T>
struct Foo<T>
{
    Foo(T member) : m_member{member} {}
        
    template <typename F>
    auto get() -> typename std::enable_if<std::is_same<F,T>::value, T>::type
    {
        return m_member;
    }
    
    template <std::size_t N>
    auto get() -> typename std::enable_if<N == 0, T>::type
    {
        return m_member;
    }

private:
    T m_member;
};

int main()
{
    Foo<char,int,bool,double> f{ 'a' , 42 , true , 1.234 };
    std::cout << f.get<char>() << std::endl;
    std::cout << f.get<int>() << std::endl;
    std::cout << f.get<bool>() << std::endl;
    std::cout << f.get<double>() << std::endl;
    
    std::cout << f.get<3>() << std::endl;
    std::cout << f.get<2>() << std::endl;
    std::cout << f.get<1>() << std::endl;
    std::cout << f.get<0>() << std::endl;
}
