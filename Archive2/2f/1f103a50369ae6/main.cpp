
#include <type_traits>

template<int ...N> 
struct list { using type = list<N...>; };

template<int N, typename IntList> 
struct prepend;

template<int N, int ... ints> 
struct prepend<N, list<ints...>>  : list<N, ints...> {};

namespace detail
{
    template<int A, int B> 
    struct min : std::integral_constant<int, (A < B ? A : B)> {};
    
    template<int A, int B> 
    struct max : std::integral_constant<int, (A > B ? A : B)> {};
    
    template<int i, int ...ints> 
    struct insert_impl : list<i> {};
    
    template<int i, int A, int ...ints> 
    struct insert_impl<i, A, ints...> : prepend<min<i,A>{}, typename insert_impl<max<i,A>{}, ints...>::type> {};
    
    template<int i, typename IntList> 
    struct insert;
    
    template<int i, int ...ints> 
    struct insert<i, list<ints...>> : insert_impl<i, ints...> {};
}

template<typename IntList> 
struct sort : list<> {};

template<int A, int ...N> 
struct sort<list<A,N...>> : detail::insert<A, typename sort<list<N...>>::type> {}; 

///////////////////////////USAGE////////////////////////////////
template<int...N>
void f() 
{
    //this line is just to generate compilation error so that
    //you can see the sorted ints in the error message
    list<N...> generate_error = 0;
}

template<int...N>
void invoke_f_with(list<N...>) 
{
    f<N...>();
}
 
template<int...N>
void g()
{
  invoke_f_with(typename sort<list<N...>>::type{});
}

int main()
{
    g<4,7,2,9,3,7>();
}