#include <type_traits>
#include <tuple>

template<class... T>
struct types { };

template <typename T>
using unqualified_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

namespace detail {
    template<class F>
    struct check_deducible_signature {
        template<class G>
        static auto test(int) -> decltype(&G::operator(), void());
        template<class>
        static auto test(...) -> struct nat;
        
        using type = std::is_void<decltype(test<F>(0))>;
    };
    
    template <typename T>
    struct non_functor_function_traits;
    
    template<typename T, typename R, typename... Args>
    struct non_functor_function_traits<R( T::* )( Args... )> {
        static const std::size_t arity = sizeof...( Args );
        static const bool is_member_function = true;
    	typedef std::tuple<Args...> arg_tuple_type;
    	typedef types<Args...> args_type;
    	typedef R( T::* function_pointer_type )( Args... );
    	typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    	typedef R( *free_function_pointer_type )( Args... );
    	typedef R return_type;
    	typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    	template<std::size_t i>
    	using arg = typename std::tuple_element<i, arg_tuple_type>::type;
    };
    
    template<typename T, typename R, typename... Args>
    struct non_functor_function_traits<R( T::* )( Args... ) const> {
    	static const std::size_t arity = sizeof...( Args );
    	static const bool is_member_function = true;
    	typedef std::tuple<Args...> arg_tuple_type;
    	typedef types<Args...> args_type;
    	typedef R( T::* function_pointer_type )( Args... );
    	typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    	typedef R( *free_function_pointer_type )( Args... );
    	typedef R return_type;
    	typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    	template<std::size_t i>
    	using arg = typename std::tuple_element<i, arg_tuple_type>::type;
    };
    
    template<typename R, typename... Args>
    struct non_functor_function_traits<R( Args... )> {
    	static const std::size_t arity = sizeof...( Args );
    	static const bool is_member_function = false;
    	typedef std::tuple<Args...> arg_tuple_type;
    	typedef types<Args...> args_type;
    	typedef R( function_type )( Args... );
    	typedef R( *function_pointer_type )( Args... );
    	typedef R( *free_function_pointer_type )( Args... );
    	typedef R return_type;
    	typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    	template<std::size_t i>
    	using arg = typename std::tuple_element<i, arg_tuple_type>::type;
    };
    
    template<typename R, typename... Args>
    struct non_functor_function_traits<R( *)( Args... )> {
    	static const std::size_t arity = sizeof...( Args );
    	static const bool is_member_function = false;
    	typedef std::tuple<Args...> arg_tuple_type;
    	typedef types<Args...> args_type;
    	typedef R( function_type )( Args... );
    	typedef R( *function_pointer_type )( Args... );
    	typedef R( *free_function_pointer_type )( Args... );
    	typedef R return_type;
    	typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    	template<std::size_t i>
    	using arg = typename std::tuple_element<i, arg_tuple_type>::type;
    };
}

template<class F>
struct has_deducible_signature : detail::check_deducible_signature<F>::type{};
    
template <typename T>
using has_deducible_signature_t = typename has_deducible_signature<T>::type;

template <typename T, bool = has_deducible_signature<T>::value>
struct function_traits : public detail::non_functor_function_traits<T> {};

template <typename T>
struct function_traits<T, true> : detail::non_functor_function_traits<decltype(&unqualified_t<T>::operator())> {};

template <typename T>
using function_args_t = typename function_traits<T>::args_type;

template <typename T>
using function_signature_t = typename function_traits<T>::signature_type;

#include <iostream>

namespace detail {
    
    template<class R, class... Args, class F, class = typename std::result_of<unqualified_t<F>( Args... )>::type>
    auto resolve_i ( types<R( Args... )>, F&& f ) -> R( unqualified_t<F>::* )( Args... ) { 
        typedef R( Sig )( Args... );
        return static_cast<Sig unqualified_t<F>::*>( &unqualified_t<F>::operator() );
    }
    
    template<class F>
    auto resolve_f( std::true_type, F&& f ) -> decltype(resolve_i( types<function_signature_t<decltype(&unqualified_t<F>::operator())>>( ), std::forward<F>(f) )) {
        return resolve_i( types<function_signature_t<decltype(&unqualified_t<F>::operator())>>( ), std::forward<F>(f) );
    }
    
    template<class F>
    void resolve_f( std::false_type, F&& f ) {
        static_assert( has_deducible_signature<F>::value, "Cannot use no-template-parameter call with an overloaded functor: specify the signature" );
    }
    
    template<class F>
    auto resolve_i( types<>, F&& f ) -> decltype(resolve_f( has_deducible_signature<unqualified_t<F>>{}, std::forward<F>(f) )) {
        return resolve_f( ::has_deducible_signature<unqualified_t<F>>{}, std::forward<F>(f) );
    }
    
    template<class... Args, class F, class R = typename std::result_of<F&( Args... )>::type>
    auto resolve_i( types<Args...>, F&& f ) -> decltype(resolve_i( types<R( Args... )>( ), std::forward<F>(f) )) {
    	return resolve_i( types<R( Args... )>( ), std::forward<F>(f) );
    }
    
    template<class Sig, class C>
    Sig C::* resolve_v( std::false_type, Sig C::* mem_func_ptr ) {
        return mem_func_ptr;
    }
    
    template<class Sig, class C>
    Sig C::* resolve_v( std::true_type, Sig C::* mem_variable_ptr ) {
        return mem_variable_ptr;
    }
}

template<class... Args, class R>
auto resolve ( R fun_ptr( Args... ) ) -> R (*)( Args... ) { 
    return fun_ptr;
}

template<class Sig>
Sig* resolve( Sig* fun_ptr ) { 
    return fun_ptr;
}

template<class... Args, class R, class C>
auto resolve ( R( C::*mem_ptr )( Args... ) ) -> R( C::* )( Args... ) {
    return mem_ptr;
}

template<class Sig, class C>
Sig C::* resolve( Sig C::* mem_ptr ) {
	return detail::resolve_v( std::is_member_object_pointer<Sig C::*>(), mem_ptr );
}

template<class... Sig, class F>
auto resolve( F&& f ) -> decltype(detail::resolve_i( types<Sig...>( ), std::forward<F>( f ) )) {
	return detail::resolve_i( types<Sig...>( ), std::forward<F>( f ) );
}

void f( int ) { }
void f( int, int ) { }

struct X {
	void f( int ) { }
	void f( int, int ) { }
};

struct Y {
	void operator()( int ) { }
	void operator()( int, int ) { }
};

struct Z {
    void operator()( double ) { }
};

struct A {
	int a;
};

int main( ) {
	resolve( &A::a );

    resolve( Z{} );

	resolve<int>( &X::f );
	resolve<void( int, int )>( &X::f );

	resolve<int>( Y{ } );
	resolve<void( int, int )>( Y{ } );

	resolve<int>( f );
	resolve<int, int>( f );
    resolve<void( int, int )>( f );
    //resolve( Y{} );
}