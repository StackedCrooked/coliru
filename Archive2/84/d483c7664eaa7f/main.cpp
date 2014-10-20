#include <type_traits>
#include <vector>

template<typename Type, typename...> struct depend_on { using type = Type; };
template<typename Type, typename... Dependee> using depend_on_t = typename depend_on<Type, Dependee...>::type;

template<typename Type>
struct foo {
    std::vector<Type> v;
    
    /*
    // Type is not dependent!
    template<std::enable_if_t<!std::is_same<Type, double>::value, int>...>
    std::size_t broken() const { return v.size(); }
    
    template<std::enable_if_t<std::is_same<Type, double>::value, int>...>
    std::size_t broken() const { return v.size() * 3; }
    */
    
    template<typename D = void, std::enable_if_t<!std::is_same<depend_on_t<Type, D>, double>::value, int>...>
    std::size_t size() const { return v.size(); }
    
    template<typename D = void, std::enable_if_t<std::is_same<depend_on_t<Type, D>, double>::value, int>...>
    std::size_t size() const { return v.size() * 3; }
};

#include <cassert>

int main()
{
    foo<int> f { { 0, 1, 2, 3, 4, 5 }};
    assert( f.size() == 6 );
    
    foo<double> g { { 0, 1, 2, 3, 4, 5 }};
    assert( g.size() == 6*3 );
}