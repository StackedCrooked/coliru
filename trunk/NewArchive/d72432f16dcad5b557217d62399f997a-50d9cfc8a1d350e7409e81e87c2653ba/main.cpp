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
    // the first overload worked and T has a nested type named foobar.
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

template <typename T, typename TDx>
class handle;

template< typename T, typename TDx>
class ptrhandle_type {
public:
	typedef handle<T, TDx> parent_type;
	typedef typename parent_type::handle_type handle_type;
	
private:
	parent_type* h;
	handle_type a;
	ptrhandle_type(const ptrhandle_type& nocopy) { };
	ptrhandle_type& operator=(const ptrhandle_type& nocopy) { return *this; };

public:
	ptrhandle_type (parent_type& ptr) : h(&ptr), a(ptr.release()) {}
	ptrhandle_type(ptrhandle_type&& mov) {h = mov.h; a = mov.a; mov.h = nullptr;}
	ptrhandle_type& operator=(ptrhandle_type&& mov) {h = mov.h; a = mov.a; mov.h = nullptr; return *this;}
	operator handle_type*() { return &a; }
	operator handle_type&() { return a; }
	~ptrhandle_type () {if ( h ) h->reset( a ); }
};

template< typename T, typename TDx>
ptrhandle_type<T,TDx> ptrhandle ( handle<T, TDx>& ptr ) { return ptrhandle_type<T, TDx>( ptr ); }

template <typename T, typename TDx = default_handle_deleter<T> >
class handle {
public:
	typedef typename handle_enable_if<has_typedef_handle_type<TDx>::value, TDx, T>::type handle_type;
	typedef TDx deleter_type;
	
private:
	handle_type res_nil;
	handle_type res;
	TDx deleter;

public:

	handle ( handle_type h, handle_type nil = default_handle_null<handle_type>::value )
	: res_nil( nil ), res( h ) {
	}

	handle ( std::nullptr_t, handle_type nil = default_handle_null<handle_type>::value ) 
	: res_nil( nil ), res( nil ) {
	}

	handle ( handle_type h, const deleter_type& d, handle_type nil = default_handle_null<handle_type>::value )
		: res_nil( nil ), res( h ), deleter( d ) {
	}

	handle ( std::nullptr_t, const deleter_type& d, handle_type nil = default_handle_null<handle_type>::value )
		: res_nil( nil ), res( nil ), deleter( d ) {
	}

	handle ( handle_type h, deleter_type&& d, handle_type nil = default_handle_null<handle_type>::value ) 
		: res_nil(nil), res( h ), deleter( std::move(d) ) {
	}

	handle ( std::nullptr_t, deleter_type&& d, handle_type nil = default_handle_null<handle_type>::value ) 
		: res_nil(nil), res( nil ), deleter( std::move(d) ) {
	}

	template <typename ...Dx>
	handle ( handle_type h, Dx&&... dx, handle_type nil = default_handle_null<handle_type>::value )
		: res_nil( nil ), res( h ), deleter( std::forward<Dx>( dx )... ) {
	}

	template <typename ...Dx>
	handle ( std::nullptr_t, Dx&&... dx, handle_type nil = default_handle_null<handle_type>::value )
		: res_nil( nil ), res( nil ), deleter( std::forward<Dx>( dx )... ) {
	}

	handle ( handle&& mov )
	: res_nil( std::move( mov.res_nil ) ), res( std::move( mov.res )), 
	deleter( std::move( mov.deleter ) ) {
		mov.reset( nullptr );
	}
	
	handle_type get () const {
		return res;
	}

	void reset ( handle_type h ) {
		if ( res != res_nil ) {
			deleter( res );
		}
		res = h;
	}

	void reset ( std::nullptr_t ) {
		if ( res != res_nil ) {
			deleter( res );
		}
		res = res_nil;
	}

	handle_type release () {
		handle_type rel = res;
		res = res_nil;
		return rel;
	}

	void swap ( handle& handler ) {
		handle_type htmp = handler.res,
			hntmp = handler.res_nil;
		deleter_type dtmp = handler.deleter;

		handler.res = res;
		handler.res_nil = res_nil;
		handler.deleter = deleter;

		res = htmp;
		res_nil = hntmp;
		deleter = dtmp;
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

	operator bool ( ) const { return get() != nullptr; }
	handle& operator= ( handle&& right ) { reset( right.release() ); return *this; }
	handle& operator= ( handle_type right ) { reset( right ); return *this; }

	operator handle_type () { return get(); };
	operator const handle_type () const { return get(); };
	ptrhandle_type<T, TDx> operator& () { return get_ptrhandle(); }
	ptrhandle_type<T, TDx> get_ptrhandle() { return ptrhandle( *this ); }

	~handle () {
		if ( res != res_nil )
			deleter( res );
		res = res_nil;
	}
};

template<typename T, typename TDx>
static bool operator== ( typename handle<T, TDx>::handle_type right, const handle<T, TDx>& left ) { return left.get() == right; }
template<typename T, typename TDx>
static bool operator== ( std::nullptr_t right, const handle<T, TDx>& left ) { return left.get() == left.res_nil; }
template<typename T, typename TDx>
static bool operator== ( const handle<T, TDx>& left, const handle<T, TDx>& right ) { return left.get() == right.get(); }
template<typename T, typename TDx>
static bool operator== ( const handle<T, TDx>& left, const typename handle<T, TDx>::parent_type& right ) { return left.get() == right.get(); }
template<typename T, typename TDx>
static bool operator== ( const handle<T, TDx>& left, typename handle<T, TDx>::handle_type right ) { return left.get() == right; }
template<typename T, typename TDx>
static bool operator== ( const handle<T, TDx>& left, std::nullptr_t right ) { return left.get() == right; }

template<typename T, typename TDx>
static bool operator!= ( typename handle<T, TDx>::handle_type right, const handle<T, TDx>& left ) { return left.get() != right; }
template<typename T, typename TDx>
static bool operator!= ( const handle<T, TDx>& left, const typename handle<T, TDx>::parent_type& right ) { return left.get() != right.get(); }
template<typename T, typename TDx>
static bool operator!= ( std::nullptr_t right, const handle<T, TDx>& left ) { return left.get() != left.res_nil; }
template<typename T, typename TDx>
static bool operator!= ( const handle<T, TDx>& left, const handle<T, TDx>& right ) { return left.get() != right.get(); }
template<typename T, typename TDx>
static bool operator!= ( const handle<T, TDx>& left, typename handle<T, TDx>::handle_type right ) { return left.get() != right; }
template<typename T, typename TDx>
static bool operator!= ( const handle<T, TDx>& left, std::nullptr_t right ) { return left.get() != left.res_nil; }

template <>
struct default_handle_null<int> {
    const static int value;
};

const int default_handle_null<int>::value = 0;

void glDeleteShader ( int* id ) {
   std::cout << "WHAM, POW, BABOW: " << *id << " bites the dust!" << std::endl; 
}

void glNotFaggotDeleteShader ( int& id ){ 
   glDeleteShader( &id );
}

int main ( int argc, char* argv[] ) {
    handle<int> testing = 500;
    std::cout << testing.get() << std::endl;
    testing.release();
    std::cout << testing.get() << std::endl;
    testing = 250;
    std::cout << testing.get() << std::endl;
    handle<int> x;
    x = std::move(testing);
    
    std::cout << std::endl;
    std::cout << "Oho, fufufu fu~" << std::endl;
    handle<int, decltype( &glNotFaggotDeleteShader )> glid( nullptr, &glNotFaggotDeleteShader );
    handle<int, decltype( &glNotFaggotDeleteShader )> deadglid( nullptr, &glNotFaggotDeleteShader );

    std::cout << testing.get() << std::endl;
    std::cout << glid.get() << std::endl;
    
    std::cout << "Transferring ownership of testing to glid, fufu~" << std::endl;
    glid = testing.release();
    
    std::cout << testing.get() << std::endl;
    std::cout << glid.get() << std::endl;

    std::cout << "Ah ka ka ka! Letting the stack die!" << std::endl;
    
}