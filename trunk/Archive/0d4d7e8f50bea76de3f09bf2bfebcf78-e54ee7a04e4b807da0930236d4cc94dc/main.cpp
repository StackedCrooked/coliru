#include <string> 
#include <iostream> 
#include <utility> 
#include <type_traits> 
#include <boost/mpl/pair.hpp> 
#include <boost/mpl/map.hpp> 
#include <boost/mpl/at.hpp> 
#include <boost/mpl/if.hpp> 
#include <boost/mpl/has_key.hpp> 
#include <boost/mpl/insert.hpp> 
  
template <char... c> struct literal 
{ 
    static constexpr char str[sizeof...( c ) + 1] = { c... }; 
    typedef literal type; 
}; 
template <char... c> 
constexpr char literal<c...>::str[]; 
  
template <typename... s> struct concat 
    : concat<typename s::type...> {}; 
template <char... c1, char... c2, typename... s> struct concat<literal<c1...>,literal<c2...>, s...> 
    : concat<literal<c1..., c2...>, s...> {}; 
template <char... c> struct concat<literal<c...>> 
    : literal<c...> {}; 
template <> struct concat<> 
    : literal<> {}; 
  
template <std::size_t N, typename L = literal<>> struct N_to_literal 
    : N_to_literal<N / 10, concat<literal<('0' + N % 10)>,L>> {}; 
template <typename L> struct N_to_literal<0, L> 
    : L {}; 
template <> struct N_to_literal<0, literal<>> 
    : literal<'0'> {}; 
  
typedef boost::mpl::map< 
    boost::mpl::pair<void,               literal<'v','o','i','d'>>, 
    boost::mpl::pair<char,               literal<'c','h','a','r'>>, 
    boost::mpl::pair<signed char,        literal<'s','i','g','n','e','d',' ','c','h','a','r'>>, 
    boost::mpl::pair<unsigned char,      literal<'u','n','s','i','g','n','e','d',' ','c','h','a','r'>>, 
    boost::mpl::pair<short,              literal<'s','h','o','r','t'>>, 
    boost::mpl::pair<unsigned short,     literal<'u','n','s','i','g','n','e','d',' ','s','h','o','r','t'>>, 
    boost::mpl::pair<int,                literal<'i','n','t'>>, 
    boost::mpl::pair<unsigned,           literal<'u','n','s','i','g','n','e','d'>>, 
    boost::mpl::pair<long,               literal<'l','o','n','g'>>, 
    boost::mpl::pair<unsigned long,      literal<'u','n','s','i','g','n','e','d',' ','l','o','n','g'>>, 
    boost::mpl::pair<long long,          literal<'l','o','n','g',' ','l','o','n','g'>>, 
    boost::mpl::pair<unsigned long long, literal<'u','n','s','i','g','n','e','d',' ','l','o','n','g',' ','l','o','n','g'>>, 
    boost::mpl::pair<wchar_t,            literal<'w','c','h','a','r','_','t'>>, 
    boost::mpl::pair<char16_t,           literal<'c','h','a','r','1','6','_','t'>>, 
    boost::mpl::pair<char32_t,           literal<'c','h','a','r','3','2','_','t'>>, 
    boost::mpl::pair<float,              literal<'f','l','o','a','t'>>, 
    boost::mpl::pair<double,             literal<'d','o','u','b','l','e'>>, 
    boost::mpl::pair<long double,        literal<'l','o','n','g',' ','d','o','u','b','l','e'>>, 
    boost::mpl::pair<std::nullptr_t,     literal<'s','t','d',':',':','n','u','l','l','p','t','r','_','t'>>> fundamental_types; 
  
template <typename L, typename R, bool b> struct type_name_parts 
{ 
    typedef L left; 
    typedef R right; 
    static constexpr bool right_last = b; 
}; 
  
template <typename T, typename M> struct derive_name_parts; 
  
template <typename T, typename M = fundamental_types> struct type_name 
    : concat<typename derive_name_parts<T, M>::left, typename derive_name_parts<T, M>::right> {}; 
  
template <typename P, typename S> struct derive_left 
    : type_name_parts< 
        concat<typename P::left, boost::mpl::if_c<P::right_last, literal<'('>, literal<>>, S>, 
        concat<boost::mpl::if_c<P::right_last, literal<')'>, literal<>>, typename P::right>, 
        false> {}; 
  
template <typename P, typename S> struct derive_right 
    : type_name_parts<typename P::left, concat<S, typename P::right>, true> {}; 
  
template <typename P, typename S> struct mem_fun_suffix 
    : type_name_parts<typename P::left, concat<typename P::right, S>, true> {}; 
  
template <typename M, typename...> struct pretty_args; 
template <typename M> struct pretty_args<M> 
    : literal<> {}; 
template <typename M, typename T> struct pretty_args<M, T> 
    : type_name<T, M> {}; 
template <typename M, typename T, typename... Args> struct pretty_args<M, T, Args...> 
    : concat<pretty_args<M, T>,literal<','>, pretty_args<M, Args...>> {}; 
  
template <typename T, typename M> struct derive_name_parts 
    : type_name_parts<boost::mpl::if_<boost::mpl::has_key<M, T>, boost::mpl::at<M, T>, literal<'u','n','k','n','o','w','n'>>, literal<>, false> {}; 
  
template <typename T, typename M> struct derive_name_parts<const T, M> 
    : derive_left<derive_name_parts<T, M>, literal<' ','c','o','n','s','t'>> {}; 
template <typename T, typename M> struct derive_name_parts<volatile T, M> 
    : derive_left<derive_name_parts<T, M>, literal<' ','v','o','l','a','t','i','l','e'>> {}; 
template <typename T, typename M> struct derive_name_parts<const volatile T, M> 
    : derive_left<derive_name_parts<T, M>, literal<' ','c','o','n','s','t',' ','v','o','l','a','t','i','l','e'>> {}; 
template <typename T, typename M> struct derive_name_parts<T*, M> 
    : derive_left<derive_name_parts<T, M>, literal<'*'>> {}; 
template <typename T, typename M> struct derive_name_parts<T&, M> 
    : derive_left<derive_name_parts<T, M>, literal<'&'>> {}; 
template <typename T, typename M> struct derive_name_parts<T&&, M> 
    : derive_left<derive_name_parts<T, M>, literal<'&','&'>> {}; 
template <typename T, typename M, std::size_t N> struct derive_name_parts<T[N], M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'['>,N_to_literal<N>,literal<']'>>> {}; 
template <typename T, typename M> struct derive_name_parts<T[], M> 
    : derive_right<derive_name_parts<T, M>, literal<'[',']'>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...), M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) const, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','c','o','n','s','t'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) volatile, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','v','o','l','a','t','i','l','e'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) const volatile, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','c','o','n','s','t',' ','v','o','l','a','t','i','l','e'>>> {}; 

#if 0
// again... 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) &, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','&'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) const &, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','c','o','n','s','t',' ','&'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) volatile &, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','v','o','l','a','t','i','l','e',' ','&'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) const volatile &, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','c','o','n','s','t',' ','v','o','l','a','t','i','l','e',' ','&'>>> {}; 
// yet again... 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) &&, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','&','&'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) const &&, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','c','o','n','s','t',' ','&','&'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) volatile &&, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','v','o','l','a','t','i','l','e',' ','&','&'>>> {}; 
template <typename T, typename M, typename... Args> struct derive_name_parts<T(Args...) const volatile &&, M> 
    : derive_right<derive_name_parts<T, M>, concat<literal<'('>, pretty_args<M, Args...>, literal<')',' ','c','o','n','s','t',' ','v','o','l','a','t','i','l','e',' ','&','&'>>> {}; 
// 
#endif

template <typename T, typename M, typename C> struct derive_name_parts<T C::*, M> 
    : derive_left<derive_name_parts<T, M>, concat<literal<' '>, type_name<C, M>, literal<':',':','*'>>> {}; 
  
int main() 
{ 
    struct Foo; 
    std::cout << type_name<int>::type::str << '\n'; 
    std::cout << type_name<int const>::type::str << '\n'; 
    std::cout << type_name<int*>::type::str << '\n'; 
    std::cout << type_name<int&&>::type::str << '\n'; 
    std::cout << type_name<int[]>::type::str << '\n'; 
    std::cout << type_name<int(void)>::type::str << '\n'; 
    std::cout << type_name<int(*)[12345]>::type::str << '\n'; 
    std::cout << type_name<void(int)>::type::str << '\n'; 
    std::cout << type_name<int&(int*, char)>::type::str << '\n'; 
    std::cout << type_name<int&(int*, char, int&(*&)(long,long long))>::type::str << '\n'; 
    std::cout << type_name<Foo>::type::str << '\n'; 
    std::cout << type_name<int Foo::*>::type::str << '\n'; 
    std::cout << type_name<int (Foo::*)()>::type::str << '\n'; 
    std::cout << type_name<int (Foo::*)(int, char)const volatile>::type::str << '\n'; 
  
    typedef boost::mpl::insert< 
        boost::mpl::insert<fundamental_types, boost::mpl::pair<Foo, literal<'F','o','o'>>>::type, 
        boost::mpl::pair<std::string, literal<':',':','s','t','d',':',':','s','t','r','i','n','g'>>>::type more_types; 
    std::cout << type_name<Foo, more_types>::type::str << '\n'; 
    std::cout << type_name<int Foo::*, more_types>::type::str << '\n'; 
    std::cout << type_name<int (Foo::*)(), more_types>::type::str << '\n'; 
    std::cout << type_name<int (Foo::*)()&, more_types>::type::str << '\n'; 
    std::cout << type_name<std::string (Foo::*)(int, char)const volatile, more_types>::type::str << '\n'; 
}