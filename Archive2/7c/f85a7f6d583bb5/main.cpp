#include <iostream>

template < typename T > struct test
{
    template < typename R = T, typename U = T, typename = void > struct bar { static constexpr R value = 0 ; };
    template < typename R, typename VOID > struct bar<R,char,VOID> { static constexpr R value = 1 ; };
    template < typename R, typename VOID > struct bar<R,wchar_t,VOID> { static constexpr R value = 2 ; };

    template < typename R = unsigned int > constexpr R foo() const { return bar<R,T>::value ; }
};

int main()
{
    test<int> i ;
    std::cout << i.foo() << '\n' ; // 0

    test<char> c ;
    std::cout << c.foo() << '\n' ; // 1

    test<wchar_t> w ;
    std::cout << w.foo() << '\n' ; // 2
}
