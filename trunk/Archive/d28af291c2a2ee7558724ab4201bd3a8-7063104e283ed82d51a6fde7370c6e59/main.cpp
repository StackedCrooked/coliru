#include <memory>

template <typename T, typename... Tn>
    ptr<T> make_ptr(std::false_type, Tn&&... argn) {
		return ptr<T>(new T(std::forward<Tn>(argn)...));
	}

	template <typename T, typename... Tn>
	ptr<T> make_ptr(std::true_type, Tn&&... argn) {
		static_assert(std::extent<T>::value == 0,
			"make_ptr<T[N]>() is forbidden, please use make_ptr<T[]>().");

		typedef typename std::remove_extent<T>::type U;
		return ptr<T>(new U[sizeof...(Tn)]{std::forward<Tn>(argn)...});
	}

	template <typename T, typename... Tn>
	ptr<T> make_ptr( Tn&&... argn ) {
		return make_ptr<T>( std::is_array<T>(), std::forward<Tn>(argn)...);
	}

	template <std::size_t n, typename T, typename TAlloc>
	cascading_construct ( std::size_t count, TAlloc&& alloc, T* ptr ) {

	}

	template <std::size_t n, typename T, typename TAlloc, typename T0, typename... Tn>
	cascading_construct ( std::size_t count, TAlloc&& alloc, T* ptr, T0&& arg, Tn&&.. argn ) {
		alloc.construct( ptr, std::forward<T0>( arg ) );
		cascading_construct<n>( ++count, std::forward<TAlloc>( alloc ), ++ptr, std::forward<Tn>( argn )... );
	}

	template <typename T, typename TAlloc, typename... Tn>
	ptr<T, allocator_deleter<TAlloc>> make_ptr_deleter(std::false_type, TAlloc&& alloc, Tn&&... argn) {
		U* ptr = alloc.allocate( 1 );
		alloc.construct( ptr, std::forward<Tn>(argn)... );
		return ptr<T, allocator_deleter<TAlloc>>( ptr, allocator_deleter<TAlloc>( alloc, 1 ) );
	}

	template <typename T, typename TAlloc, typename... Tn>
	ptr<T, allocator_deleter<TAlloc>> make_ptr_deleter(std::true_type, TAlloc&& alloc, Tn&&... argn) {
		static_assert(std::extent<T>::value == 0,
			"make_ptr<T[N]>() is forbidden, please use make_ptr<T[]>().");

		typedef typename std::remove_extent<T>::type U;
		U* ptr = alloc.allocate( sizeof...( Tn ) );
		cascading_construct<sizeof...( Tn )>( 0, alloc, ptr );
		return ptr<T, allocator_deleter<TAlloc>>( ptr, allocator_deleter<TAlloc>( alloc, sizeof...( Tn ) ) );
	}

	template <typename T, typename TAlloc, typename... Tn>
	ptr<T, allocator_deleter<TAlloc>> make_ptr_deleter( Tn&&... argn ) {
		return make_ptr_deleter<T, TAlloc>( std::is_array<T>(), std::forward<Tn>(argn)... );
	}


int main ( int argc, char** argv ) {
    
    
    
}