#include <type_traits>
#include <iostream>
class A; class B; class C;

template<std::size_t Cur, class T, class...TArgs>
    struct index_of;
    
    template<std::size_t Cur, class T, class...TArgs>
    struct index_of<Cur, T, T, TArgs...> : std::integral_constant<std::size_t, Cur> {};
    
    template<std::size_t Cur, class T, class T1, class...TArgs>
    struct index_of<Cur, T, T1, TArgs...> : index_of<Cur + 1, T, TArgs...> {};
    
    template<class T, class...TArgs>
    using index_of_t = index_of<0, T, TArgs...>;

template<typename... TArgs>
struct Foo
{
  template<typename T>
  int get_idx()
  {
    return index_of_t<T, TArgs...>::value;
  }
};

int main(){
    Foo<A,B,C> foo;
    std::cout << foo.get_idx<B>() << std::endl;
}