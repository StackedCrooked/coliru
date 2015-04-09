#include <utility>
#include <iostream>

template<class...>struct voider{using type=void;};
template<class...Ts>using void_t=typename voider<Ts...>::type;
template<class T>struct tag{using type=T;};

template<class...>struct types{using type=types;};

template<class T>
using block_deduction = typename tag<T>::type;

template<class F, class Sig, class T=void>
struct erase_view_op;

template<class F, class R, class...Ts, class T>
struct erase_view_op<F, R(Ts...), T>
{
    using fptr = R(*)(void const*, Ts&&...);
    
    fptr f;
    void const* ptr;
    
private:
    template<class U>
    erase_view_op(U&& u, int):
        f([](void const* p, Ts&&...ts)->R{
            U& u = reinterpret_cast<U&>( *static_cast<std::decay_t<U>*>(const_cast<void*>(p)) );
            return F{}( u, std::forward<Ts>(ts)... );
        }),
        ptr( static_cast<void const*>(u) )
    {}
public:
    template<class U, class=std::enable_if_t< !std::is_same<std::decay_t<U>,erase_view_op>{} && std::is_convertible< std::result_of_t<F(U,Ts...)>, R >{} >>
    erase_view_op(U&& u):erase_view_op( std::forward<U>(u), 0 ){}
    
    template<class U=T, class=std::enable_if_t< !std::is_same<U, void>{} >>
    erase_view_op( block_deduction<U>&& u ):erase_view_op( std::move(u), 0 ){}
    
    erase_view_op( erase_view_op const& ) = default;
    erase_view_op( erase_view_op&& ) = default;
    
    R operator()( Ts... ts ) const {
        return f( ptr, std::forward<Ts>(ts)... );
    }
};

struct equality {
    template<class lhs, class rhs>
    bool operator()(lhs const& l, rhs const& r)const {
        return l==r;
    }
};
template<class T>
using erase_equal_to = erase_view_op< equality, bool(T const&), T >;
using string_equal_to = erase_equal_to< std::string >;

int main() {
    static_assert( std::is_same< bool, std::result_of_t< std::equal_to<>(decltype("hello"), std::string const&) > >{}, "hmm" );
    string_equal_to s = "hello";
    std::string x = "hello";
    std::string y = "jello";
    std::cout << s(x) << s(y) << '\n';
}