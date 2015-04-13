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
        ptr( static_cast<void const*>(std::addressof(u)) )
    {}
public:
    template<class U, class=std::enable_if_t< !std::is_same<std::decay_t<U>,erase_view_op>{} && (std::is_same<void,R>{} || std::is_convertible< std::result_of_t<F(U,Ts...)>, R >{}) >>
    erase_view_op(U&& u):erase_view_op( std::forward<U>(u), 0 ){}
    
    template<class U=T, class=std::enable_if_t< !std::is_same<U, void>{} >>
    erase_view_op( block_deduction<U>&& u ):erase_view_op( std::move(u), 0 ){}
    
    erase_view_op( erase_view_op const& ) = default;
    erase_view_op( erase_view_op&& ) = default;
    
    R operator()( Ts... ts ) const {
        return f( ptr, std::forward<Ts>(ts)... );
    }
};

struct assign_lhs_to_rhs {
    template<class lhs, class rhs>
    void operator()(lhs&& l, rhs& r)const {
        r = std::forward<lhs>(l);
    }
};
template<class T>
using erase_assignment_to = erase_view_op< assign_lhs_to_rhs, void(T&), T >;
using string_assign_to = erase_assignment_to< std::string >;

struct test_class {
    std::string data;
    void set_data( string_assign_to s ) {
        s(data);
    }
};
int main() {
    test_class test;
    test.set_data( "hello" );
    std::cout << test.data << '\n';
}