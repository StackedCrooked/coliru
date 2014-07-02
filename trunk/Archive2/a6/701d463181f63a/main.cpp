#include <type_traits>
#include <tuple>

#include <iostream>

template<class... T>
struct types { };

template <typename T>
using unqualified_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename T>
struct function_traits;

template <typename T>
using function_args_t = typename function_traits<T>::args_type;

template <typename T>
using function_signature_t = typename function_traits<T>::signature_type;

template<typename T, typename R, typename... Args>
struct function_traits<R( T::* )( Args... )> {
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
struct function_traits<R( T::* )( Args... ) const> {
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
struct function_traits<R( Args... )> {
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
struct function_traits<R( *)( Args... )> {
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

template<class F>
void set_i( types<>, F&& f ) {
    std::cout << "traited ";
    set_i( types<function_signature_t<decltype(&unqualified_t<F>::operator())>>( ), std::forward<F>(f) );
}


template<class... Args, class F,
class R = typename std::result_of<F&( Args... )>::type>
void set_i( types<Args...>, F&& f ) {
	std::cout << "argumented ";
    set_i( types<R( Args... )>( ), std::forward<F>(f) );
}

template<class R, class... Args, class F,
class = typename std::result_of<unqualified_t<F>( Args... )>::type>
void set_i( types<R( Args... )>, F&& f ) { 
    std::cout << "signature ";
    std::cout << "Functor, resolved\n";
}

template<class Sig, class C>
void set_v( std::false_type, Sig C::* mem_ptr ) {
    std::cout << "Member function pointer, signatured\n";
}

template<class Sig, class C>
void set_v( std::true_type, Sig C::* mem_ptr ) {
    std::cout << "Member variable pointer\n";
}

template<class... Args, class R>
void set( R fun_ptr( Args... ) ) { 
    std::cout << "Function pointer, argumented\n";
}

template<class Sig>
void set( Sig* fun_ptr ) { 
    std::cout << "Function pointer, signatured\n";
}

template<class Sig>
void set( Sig& fun_ptr ) { 
    std::cout << "Function reference, signatured\n";
}

template<class... Args, class R, class C>
void set( R( C::*mem_ptr )( Args... ) ) {
    std::cout << "Member function pointer, argumented\n";
}

template<class Sig, class C>
void set( Sig C::* mem_ptr ) {
	set_v( std::is_member_object_pointer<Sig C::*>(), mem_ptr );
}

template<class... Sig, class F>
void set( F&& f ) {
	set_i( types<Sig...>( ), std::forward<F>(f) );
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
	set( &A::a );

    set( Z{} );

	set<int>( &X::f );
	set<void( int, int )>( &X::f );

	set<int>( Y{ } );
	set<void( int, int )>( Y{ } );

	set<int>( f );
	set<int, int>( f );
	set<void( int, int )>( f );
}