#include <type_traits>
#include <initializer_list>
#include <utility>
#include <array>

template<typename T>
struct unqualified {
	typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
};

template <typename T>
using unqualified_t = typename unqualified<T>::type;

template <typename T, std::size_t n>
struct Vector {
	std::array<T, n> res;
    
    Vector( ) = default;
    
    Vector( std::initializer_list<T> init ) {
        std::size_t idx = 0;
        set( std::false_type(), idx, std::move(init) );
	}
    
	template <typename... Tn>
	Vector( Tn&&... argn ) {
		std::size_t idx = 0;
		using swallow = int[];
		(void)swallow{ 0, ( void( 
			set( std::is_convertible<T, unqualified_t<Tn>>(), idx, std::forward<Tn>( argn ) ) 
		), 0 )... };
        // TODO: checking to make sure there was no overflow?
        // Would ideally want at compile-time, but...
	}

	template <typename Ta>
	void set( std::true_type, std::size_t& idx, Ta&& a ) {
		res[ idx++ ] = std::forward<Ta>( a );
	}

	template <typename Tr>
	void set( std::false_type, std::size_t& idx, Tr&& r ) {
		// Assume it's a range of some sort
		// This should do ADL for us too...
		for ( const auto& elem : r ) {
			set( std::true_type( ), idx, elem );
		}
	}

	T* begin( ) {
		return data( );
	}

	const T* begin( ) const {
		return data( );
	}

	const T* cbegin( ) const {
		return data( );
	}

	T* end( ) {
		return data_end( );
	}

	const T* end( ) const {
		return data_end( );
	}

	const T* cend( ) const {
		return data_end( );
	}

	T* data( ) {
		return res.data( );
	}

	const T* data( ) const {
		return res.data( );
	}

	T* data_end( ) {
		return res.data( ) + res.size( );
	}

	const T* data_end( ) const {
		return res.data( ) + res.size( );
	}

	T& operator [] ( std::size_t i ) {
		return res[ i ];
	}

	const T& operator [] ( std::size_t i ) const {
		return res[ i ];
	}

	static std::size_t size( ) {
		return n;
	}
};

typedef Vector<float, 3> Vector3;

#include <iostream>

template <typename T>
void print ( T&& r ) {
    for ( const auto& elem : r ) {
		std::cout << " " << elem;
	}
}

int main () {
    Vector3 garbage; // makes it usable with other primitives in crazy unions and shit
    
    Vector3 init{}; // zero-initialization: what we want for vector<> and friends
    
    Vector3 arf( 1, 2, 3 ); // still constructors fine, individual elements
    
    float some_data[2] = { 4, 5 };
    Vector3 woof(some_data, 6); // 4, 5, 6
    
    float more_data[3] = { 7, 8, 9 };
    Vector3 double_woof(more_data); // 7, 8, 9
    
    float extra_data[2] = { 14, 15 };
    Vector3 triple_woof(13, extra_data); // 13, 14, 15
    
    print( garbage );
    std::cout << '\n';
    print( init );
    std::cout << '\n';
    print( arf );
    std::cout << '\n';
    print( woof );
    std::cout << '\n';
    print( double_woof );
    std::cout << '\n';
    print( triple_woof );
    std::cout << '\n';
    
    union {
        float f[3];
        Vector3 g;
    };
}