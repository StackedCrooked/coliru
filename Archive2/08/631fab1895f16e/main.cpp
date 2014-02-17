#include <utility>
#include <type_traits>
#include <tuple>

template<bool b, class T = void>
using enable_if_t = typename std::enable_if<b, T>::type;

template<class T>
using remove_reference_t = typename std::remove_reference<T>::type;

template<bool b, class Then, class Else>
using conditional_t = typename std::conditional<b, Then, Else>::type;


template<class T> remove_reference_t<T>&& as_rvalue(T&& p) { return std::move(p); }

// by Casey, http://stackoverflow.com/questions/21781727/is-array-indexing-constexpr-or-not-gcc-inconsistent#comment32959077_21782362
template <typename T> const T&  as_const(const T& t) { return t; }
template <typename T> const T&& as_const(const T&& t) { return std::move(t); }


template< int N, class Tuple, class = enable_if_t<not std::is_const<Tuple>::value> >
auto tuple_actual_element_type(Tuple& t, int)
->
conditional_t< std::is_lvalue_reference<decltype(as_rvalue(t).template get<N>())>::value,
               decltype(as_rvalue(t).template get<N>()),
               conditional_t< std::is_same<decltype(as_const(t).template get<N>()), decltype(t.template get<N>())>::value,
                              decltype(as_rvalue(t).template get<N>()),
                              remove_reference_t<decltype(as_rvalue(t).template get<N>())>
                            >
             >
;

struct begin_type {};
struct end_type {};

template< int N, class Tuple, class = enable_if_t<not std::is_const<Tuple>::value> >
auto tuple_actual_element_type(Tuple& t, short)
-> end_type;

template<class Tuple, int N = 0, class Next = begin_type, class... Found>
struct reconstruct_tuple_helper
{
    using type = typename reconstruct_tuple_helper<Tuple, N+1, decltype(tuple_actual_element_type<N>(std::declval<Tuple&>(), 0)), Found..., Next>::type;
};

/*template<class Tuple, int N, class... Found>
struct reconstruct_tuple_helper<Tuple, N, end_type, Found...>
{
    using type = std::tuple<Found...>;
};*/
template<class Tuple, class T, class... Found>
struct reconstruct_tuple_helper<Tuple, 8, T, Found...>
{
    using type = std::tuple<Found..., T>;
};

template<class Tuple, int N, class... Found>
struct reconstruct_tuple_helper<Tuple, N, begin_type, Found...>
{
    using type = typename reconstruct_tuple_helper<Tuple, N+1, decltype(tuple_actual_element_type<N>(std::declval<Tuple&>(), 0)), Found...>::type;
};


template<class... TT>
class my_tuple
{
//private:
public:
    std::tuple<TT...> m;
public:
    template<class... Args, class = enable_if_t< std::is_constructible<decltype(m), Args&&...>::value >>
    my_tuple(Args&&... args) : m(std::forward<Args>(args)...)
    {}
    
    template<int N>
    auto get() & -> decltype(std::get<N>(m))
    {  return std::get<N>(m);  }
    
    template<int N>
    auto get() && -> decltype(std::get<N>(as_rvalue(m)))
    {  return std::get<N>(m);  }
    
    template<int N>
    auto get() const & -> decltype(std::get<N>(as_const(m)))
    {  return std::get<N>(m);  }
    
    template<int N>
    auto get() const && -> decltype(std::get<N>(as_rvalue(as_const(m))))
    {  return std::get<N>(m);  }
};

#include <iostream>
template<class T>
void pretty_print()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    using test_type = my_tuple<int, int&, int&&, int const&, int const&&, int*, int const*, int const* const>;
    //static_assert( std::is_same<decltype(test_type::m), reconstruct_tuple_helper<test_type>::type>::value, "!" );
    pretty_print<reconstruct_tuple_helper<test_type>::type>();
}