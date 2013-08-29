#include <cstddef>
#include <utility>
#include <iostream>

template <typename T>
struct has_typedef_handle_type {
    // Types "yes" and "no" are guaranteed to have different sizes,
    // specifically sizeof(yes) == 1 and sizeof(no) == 2.
    typedef char yes[1];
    typedef char no[2];
 
    template <typename C>
    static yes& test(typename C::handle_type*);
 
    template <typename>
    static no& test(...);
 
    // If the "sizeof" the result of calling test<T>(0) would be equal to the sizeof(yes),
    // the first overload worked and T has a nested type named handle_type.
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <bool b, typename T, typename TFallback>
struct handle_enable_if { };

template <typename T, typename TFallback>
struct handle_enable_if<false, T, TFallback> {
	typedef TFallback type;
};

template <typename T, typename TFallback>
struct handle_enable_if<true, T, TFallback>{
	typedef typename T::handle_type type;
};

template <typename T, typename TDx>
struct get_handle_type {
	typedef typename handle_enable_if<has_typedef_handle_type<TDx>::value, TDx, T>::type type;
};

template <typename T>
struct default_handle_deleter {
    void operator () ( T& handle ) {
        // No-op; handle will invoke default destructor upon exist. 
        // You should override this
    }
};

template <typename T>
struct default_handle_null {
	const static T value;
};

template <typename T>
const T default_handle_null<T>::value;

template <typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
class ptrhandle_type;

template <typename T, 
	typename TDx = default_handle_deleter<T>, 
	typename get_handle_type<T, TDx>::type nil = default_handle_null<typename get_handle_type<T, TDx>::type>::value >
class handle {
public:
	typedef typename get_handle_type<T, TDx>::type handle_type;
	typedef TDx deleter_type;
	const static handle_type null;

private:
	handle_type res;
	TDx deleter;

	handle ( const handle& nocopy ) {}

public:

	handle ( )
		: res( nil ) {
	}

	handle ( handle_type h )
	: res( h ) {
	}

	handle ( std::nullptr_t ) 
	: res( nil ) {
	}

	handle ( handle_type h, const deleter_type& d )
	: res( h ), deleter( d ) {
	}

	handle ( std::nullptr_t, const deleter_type& d )
	: res( nil ), deleter( d ) {
	}

	handle ( handle_type h, deleter_type&& d ) 
	: res( h ), deleter( std::move( d ) ) {
	}

	handle ( std::nullptr_t, deleter_type&& d ) 
	: res( nil ), deleter( std::move( d ) ) {
	}

	template <typename ...Dx>
	handle ( handle_type h, Dx&&... dx )
	: res( h ), deleter( std::forward<Dx>( dx )... ) {
	}

	template <typename ...Dx>
	handle ( std::nullptr_t, Dx&&... dx )
	: res( nil ), deleter( std::forward<Dx>( dx )... ) {
	}

	handle ( handle&& mov )
	: res( std::move( mov.res )), 
	deleter( std::move( mov.deleter ) ) {
		mov.reset( nullptr );
	}
	
	handle_type get () const {
		return res;
	}

	void reset ( handle_type h ) {
		if ( res != nil )
			deleter( res );
		res = h;
	}

	void reset ( std::nullptr_t ) {
		if ( res != nil )
			deleter( res );
		res = nil;
	}

	handle_type release () {
		handle_type rel = res;
		res = nil;
		return rel;
	}

	void swap ( handle& handler ) {
		std::swap( handler.res, res );
		std::swap( handler.deleter, deleter );
	}

	deleter_type& get_deleter () {
		return deleter;
	}

	const deleter_type& get_deleter () const {
		return deleter;
	}

	handle_type operator* () {
		return get();
	}

	handle_type operator-> () {
		return get();
	}

	explicit operator bool ( ) const { return get() != nil; }
	handle& operator= ( handle&& right ) { reset( right.release() ); return *this; }
	handle& operator= ( handle_type right ) { reset( right ); return *this; }
	handle& operator= ( std::nullptr_t ) { reset( nullptr ); return *this; }

	operator handle_type () { return get(); }
	operator const handle_type () const { return get(); }
	ptrhandle_type<T, TDx, nil> operator& () { return get_ptrhandle(); }
	ptrhandle_type<T, TDx, nil> get_ptrhandle() { return ptrhandle( *this ); }

	~handle () {
		if ( res != nil )
			deleter( res );
		res = nil;
	}
};

template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
const typename get_handle_type<T, TDx>::type handle<T, TDx, nil>::null = nil;

template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator== ( typename handle< T, TDx, nil>::handle_type right, const handle< T, TDx, nil>& left ) { return left.get() == right; }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator== ( std::nullptr_t right, const handle< T, TDx, nil>& left ) { return left.get() == nil; }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator== ( const handle< T, TDx, nil>& left, const handle< T, TDx, nil>& right ) { return left.get() == right.get(); }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator== ( const handle< T, TDx, nil>& left, const typename handle< T, TDx, nil>::parent_type& right ) { return left.get() == right.get(); }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator== ( const handle< T, TDx, nil>& left, typename handle< T, TDx, nil>::handle_type right ) { return left.get() == right; }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator== ( const handle< T, TDx, nil>& left, std::nullptr_t right ) { return left.get() == right; }

template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator!= ( typename handle< T, TDx, nil>::handle_type right, const handle< T, TDx, nil>& left ) { return left.get() != right; }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator!= ( const handle< T, TDx, nil>& left, const typename handle< T, TDx, nil>::parent_type& right ) { return left.get() != right.get(); }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator!= ( std::nullptr_t right, const handle< T, TDx, nil>& left ) { return left.get() != nil; }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator!= ( const handle< T, TDx, nil>& left, const handle< T, TDx, nil>& right ) { return left.get() != right.get(); }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator!= ( const handle< T, TDx, nil>& left, typename handle< T, TDx, nil>::handle_type right ) { return left.get() != right; }
template<typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
static bool operator!= ( const handle< T, TDx, nil>& left, std::nullptr_t right ) { return left.get() != nil; }

template< typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
class ptrhandle_type {
public:
	typedef handle<T, TDx, nil> parent_type;
	typedef typename parent_type::handle_type handle_type;

private:
	parent_type* h;
	handle_type a;
	ptrhandle_type(const ptrhandle_type& nocopy) { };
	ptrhandle_type& operator=(const ptrhandle_type& nocopy) { return *this; };

public:
	ptrhandle_type (parent_type& ptr) : h(std::addressof( ptr )), a(ptr.release()) {}
	ptrhandle_type(ptrhandle_type&& mov) {h = mov.h; a = mov.a; mov.h = nullptr;}
	ptrhandle_type& operator=(ptrhandle_type&& mov) {h = mov.h; a = mov.a; mov.h = nullptr; return *this;}
	operator handle_type*() { return &a; }
	operator handle_type&() { return a; }
	~ptrhandle_type () {if ( h ) h->reset( a ); }
};

template< typename T, typename TDx, typename get_handle_type<T, TDx>::type nil>
ptrhandle_type<T, TDx, nil> ptrhandle ( handle<T, TDx, nil>& ptr ) { return ptrhandle_type<T, TDx, nil>( ptr ); }

template <>
struct default_handle_null<int> {
    const static int value;
};

const int default_handle_null<int>::value = 0;

void glDeleteShader ( int* id ) {
   std::cout << "WHAM, POW, BABOW: " << *id << " bites the dust!" << std::endl; 
   *id = 0;
}

void glNotFaggotDeleteShader ( int& id ){ 
   glDeleteShader( &id );
}

int main ( int argc, char* argv[] ) {
   std::cout << "Testing, initialized to 500, released, and then initialized again" << std::endl;
    handle<int> testing = 500;
	std::cout << testing.get() << std::endl;
	testing.release();
	std::cout << testing.get() << std::endl;
	testing = 250;
	std::cout << testing.get() << std::endl;

	std::cout << "X, initialized to nothing, then populated with a move from testing" << std::endl;
	handle<int> x;
	x = std::move( testing );
	std::cout << x.get() << std::endl;
	std::cout << testing.get() << std::endl;

	std::cout << "Testing to 200, Uu fufufu fu~" << std::endl;
	handle<int, decltype( &glNotFaggotDeleteShader )> glid( nullptr, &glNotFaggotDeleteShader );

	testing = 200;

	std::cout << testing.get() << std::endl;
	std::cout << glid.get() << std::endl;

	glid = testing.release();
	std::cout << testing.get() << std::endl;
	std::cout << glid.get() << std::endl;

	if ( glid )
		glDeleteShader( &glid );
    
}