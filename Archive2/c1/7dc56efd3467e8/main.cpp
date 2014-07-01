#include <type_traits>

template<class... T>
struct types { };

template<class... Args, class F,
class R = typename std::result_of<F&( Args... )>::type>
    void set_i( types<Args...>, F f ) {
	set_i( types<R( Args... )>( ), f );
}

template<class R, class... Args, class F,
class = typename std::result_of<F&( Args... )>::type>
	void set_i( types<R( Args... )>, F f ) { }

template<class Sig, class C>
void set_v( std::false_type, Sig C::* mem_ptr ) {

}

template<class Sig, class C>
void set_v( std::true_type, Sig C::* mem_ptr ) {

}

template<class... Args, class R>
void set( R fun_ptr( Args... ) ) { }

template<class Sig>
void set( Sig* fun_ptr ) { }

template<class... Args, class R, class C>
void set( R( C::*mem_ptr )( Args... ) ) {

}

template<class Sig, class C>
void set( Sig C::* mem_ptr ) {
	set_v( std::is_member_object_pointer<Sig C::*>(), mem_ptr );
}

template<class... Sig, class F>
void set( F f ) {
	set_i( types<Sig...>( ), f );
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

struct A {
	int a;
};

int main( ) {
	set( &A::a );

	set<int>( &X::f );
	set<void( int, int )>( &X::f );

	set<int>( Y{ } );
	set<void( int, int )>( Y{ } );

	set<int>( f );
	set<int, int>( f );
	set<void( int, int )>( f );
}