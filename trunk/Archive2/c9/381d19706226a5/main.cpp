
template<int ...N> struct list {};

template<int N, typename IntList> 
struct prepend;

template<int N, int ... ints> 
struct prepend<N, list<ints...>> 
{
    using type = list<N, ints...>;
};

namespace detail
{
    template<int i, typename IntList> struct insert;
    
    template<int i, int ...ints> 
    struct insert_impl
    {
        using type = list<i>;
    };

    template<int i, int A, int ...ints> 
    struct insert_impl<i, A, ints...>
    {
        const static int small = i < A ? i : A;
        const static int big = i + A - small;
        using type = typename prepend<small, typename insert_impl<big, ints...>::type>::type;
    };
    
    template<int i, int ...ints> 
    struct insert<i, list<ints...>>
    {
        using type = typename insert_impl<i, ints...>::type;
    };
}

template<typename IntList> 
struct sort 
{
    using type = list<>;
};

template<int A, int ...N> 
struct sort<list<A,N...>>
{
    using type = typename detail::insert<A, typename sort<list<N...>>::type>::type;
};

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