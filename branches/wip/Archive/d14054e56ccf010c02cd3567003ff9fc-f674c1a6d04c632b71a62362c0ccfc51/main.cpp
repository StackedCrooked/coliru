#include <memory>
#include <cstdlib>
#include <type_traits>


template<typename TFuncSignature>
struct function_traits;

template<typename R, typename T0>
struct function_traits<R ( T0 )> {

	typedef R return_type;
	typedef T0 arg0_type;
	typedef R (*func_pointer_type)( T0 );
	const static std::size_t arity = 1;

};

template<typename R, typename T0>
struct function_traits<R (*)( T0 )> {

	typedef R return_type;
	typedef T0 arg0_type;
	typedef R (*func_pointer_type)( T0 );
	const static std::size_t arity = 1;

};

template <typename TDx>
struct delete_by {
    typedef typename function_traits<TDx>::arg0_type pointer;
	TDx dx;

	delete_by ( TDx del = TDx() ) : dx( std::move( del ) ) {

	}

	void operator () ( pointer p ) {
		dx( p );
	}
};

int main() {
    
    // Holy shit this is long
    std::unique_ptr<void, delete_by<decltype( &free )>> arf( malloc( 8 ), std::free );
	arf.reset( nullptr );
    
}