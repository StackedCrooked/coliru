#include <type_traits>
#include <iostream>

typedef std::size_t ulword;

template <typename T, ulword size = sizeof(T), ulword align = std::alignment_of<T>::value>
    struct raw_structure {
		typename std::aligned_storage<size, align>::type buffer;
		
		template <typename ...Tn>
		raw_structure ( Tn&&... argn ) {
			new ( &get() )T( std::forward<Tn>( argn )... );
		}

		T& get ( ) {
			return *static_cast<T*>( (void*)&buffer );
		}

		const T& get ( ) const {
			return *static_cast<const T*>( (void*)&buffer );
		}
		
		T& operator -> ( ) {
			return get();
		}

		const T& operator -> ( ) const {
			return get();
		}

		operator T& ( ) {
			return get();
		}

		operator const T& ( ) const {
			return get();
		}

		~raw_structure() {
			get().~T();
		}
	};
    
int main ( int argc, char* argv[] ) {
    
    raw_structure<int> evadealignment;
    evadealignment = 2;
    evadealignment *= 2;
    
    std::cout << evadealignment << std::endl;
    
}