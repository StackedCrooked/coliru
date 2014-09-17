#include <iostream>
#include <type_traits>

template<typename... Types>
struct Foo;

template <typename T, typename... Types>
struct Foo<T, Types...> : Foo<Types ...>
{
    using Foo<Types...>::getMember;
    
    Foo(T member, Types... others) : Foo<Types...>{others...}, m_member{member} {}
    
    template <typename F>
    auto getMember() -> typename std::enable_if<std::is_same<F,T>::value, T>::type { return m_member; }
    
private:
    T m_member;
};

template <typename T>
struct Foo<T>
{
    Foo(T member) : m_member{member} {}
        
    template <typename F>
    auto getMember() -> typename std::enable_if<std::is_same<F,T>::value, T>::type { return m_member; }

private:
    T m_member;
};

int main()
{
    Foo<char,int,bool,double> f( 'a' , 42 , true , 1.234 );
    std::cout << f.getMember<char>() << std::endl;
    std::cout << f.getMember<int>() << std::endl;
    std::cout << f.getMember<bool>() << std::endl;
    std::cout << f.getMember<double>() << std::endl;
}
