#include <type_traits>

template<class...>
struct LCA;

template<class T, class... TT>
struct LCA<T, TT...>
{
    template<class Max, class b = std::true_type, class... UU>
    struct X
    {
        using type = Max;
    };
    
    template<class Max, class U, class... UU>
    struct X<Max, typename std::is_base_of<Max, U>::type, U, UU...>
    {
        using type = U;
    };
    
    using type = typename X<T, std::true_type, TT...>::type;
};


struct Grandma {};
struct Mom : Grandma {};
struct Son : Mom {};
struct Grandchild : Son {};


#include <iostream>
template<class T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    print_type< LCA<Son, Grandchild, Son     >::type >();
    print_type< LCA<Son, Grandchild, Mom, Son>::type >();
    print_type< LCA<Mom, Mom, Mom            >::type >();
}