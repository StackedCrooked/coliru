#include <cstddef>
#include <memory>
#include <numeric>
#include <array>
#include <initializer_list>

namespace detail {
    
	template <typename T>
	auto get_data( std::initializer_list<T>& cont ) -> decltype( cont.begin( ) ) {
		return cont.begin( );
	}

	template <typename T>
	auto get_data( std::initializer_list<T>&& cont ) -> decltype( cont.begin( ) ) {
		return cont.begin( );
	}

	template <typename T>
	auto get_data( std::initializer_list<T> cont ) -> decltype( cont.begin( ) ) {
		return cont.begin( );
	}

	template <typename T>
	auto get_data( std::false_type, T* cont ) -> decltype( cont ) {
		return cont;
	}

	template <typename T>
	auto get_data( std::false_type, T&& cont ) -> decltype( cont.data( ) ) {
		return cont.data( );
	}

	template <typename T, std::size_t n>
	T* get_data( std::true_type, T( &cont )[ n ] ) {
		return std::addressof( cont[ 0 ] );
	}

	inline std::nullptr_t get_data( std::false_type, std::nullptr_t ) {
		return nullptr;
	}

	inline std::size_t get_size( std::false_type, std::nullptr_t ) {
		return 0;
	}

	template <typename T>
	auto get_size( std::false_type, T&& cont ) -> decltype( cont.size( ) ) {
		return cont.size( );
	}

	template <typename T, std::size_t n>
	std::size_t get_size( std::true_type, T( &cont )[ n ] ) {
		return n;
	}

}

template <typename T>
auto get_data( T& cont ) -> decltype( detail::get_data( std::is_array<T>( ), cont ) ) {
	return detail::get_data( std::is_array<T>( ), cont );
}

template <typename T>
auto get_size( T& cont ) -> decltype( detail::get_size( std::is_array<T>( ), cont ) ) {
	return detail::get_size( std::is_array<T>( ), cont );
}

template <std::size_t nrank = 1>
struct index {
private:
    std::array<std::size_t, nrank> idxs;
    
public:

    index ( ) : idxs() {
        
    }
    
    index( std::initializer_list<std::size_t> values ) {
        std::copy( values.begin(), values.end(), idxs.begin() );
    }
    
    std::size_t& operator[]( std::size_t i ) {
        return idxs[i];
    }
    
    const std::size_t& operator[]( std::size_t i ) const {
        return idxs[i];
    }
};

template <>
struct index<1> {
private:
    std::array<std::size_t, 1> idxs;
    
public:
    index ( ) : idxs() {
        
    }
    
    index( std::size_t dim ) {
        idxs[0] = dim;
    }
    
    index( std::initializer_list<std::size_t> values ) {
        std::copy( values.begin(), values.end(), idxs.begin() );
    }
    
    std::size_t size () const {
        return idxs.size();
    }
    
    std::size_t& operator[]( std::size_t i ) {
        return idxs[i];
    }
    
    const std::size_t& operator[]( std::size_t i ) const {
        return idxs[i];
    }
};

template <typename TRange, std::size_t nrank>
std::size_t access_index ( const index<nrank>& i, TRange&& dimensions ) {
    std::size_t dataidx = 0;
    for ( std::size_t c = 0; c < dimensions.size() -1; ++c ) {
	    dataidx += i[c] * dimensions[c];
    }
    return i[ dimensions.size() - 1 ] + dataidx;
}

template <typename T, std::size_t d = 1>
class buffer_view {
public:
    typedef index<d> index_type;
	typedef T value_type;
	typedef typename std::conditional<std::is_same<void, typename std::remove_cv<T>::type>::value, unsigned char, T>::type& reference;
	typedef const typename std::conditional<std::is_same<void, typename std::remove_cv<T>::type>::value, unsigned char, T>::type& const_reference;
	typedef T* pointer_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef pointer_type iterator;
	typedef const pointer_type const_iterator;

private:
	T* res;
	std::array<std::size_t, d> dims;

public:

	buffer_view( std::nullptr_t nptr = nullptr ) : res( nullptr ), dims{ } {

	}

	buffer_view( T* buffer, const std::array<std::size_t, d>& dims )
		: res( buffer ), dims( dims ) {

	}

	template <typename TContainer, typename... Tn>
	buffer_view( TContainer&& container, Tn&&... sizen )
		: buffer_view( get_data( container ), { static_cast<std::size_t>( std::forward<Tn>( sizen ) )... } ) {

	}

	template <typename TContainer>
	buffer_view( TContainer&& container )
		: buffer_view( get_data( container ), { get_size( container ) } ) {
        static_assert( d == 1, "Cannot use single-argument constructor with a multi-dimensional array: specify sizes" );
	}

	const std::array<std::size_t, d>& dimensions ( ) const {
		return dims;
	}

	bool is_null( ) const {
		return res == nullptr;
	}

	bool empty( ) const {
		return size( ) < 1;
	}

	bool not_empty( ) const {
		return size( ) > 0;
	}

	iterator begin( ) {
		return res;
	}

	iterator end( ) {
		return res + size( );
	}

	const_iterator begin( ) const {
		return res;
	}

	const_iterator end( ) const {
		return res + size( );
	}

	const_iterator cbegin( ) {
		return res;
	}

	const_iterator cend( ) {
		return res + size( );
	}

	const_iterator cbegin( ) const {
		return res;
	}

	const_iterator cend( ) const {
		return res + size( );
	}

	reference operator[] ( index_type i ) {
        return res[ access_index( i, dims ) ];
    }

	const_reference operator[] ( index_type i ) const {
	    return res[ access_index( i, dims ) ];
    }

	T* data( ) {
		return res;
	}

	T* data_end( ) {
		return res + size( );
	}

	const T* data( ) const {
		return res;
	}

	const T* data_end( ) const {
		return res + size();
	}

	reference front( ) {
		return *res;
	}

	reference back( ) {
		return *( res + size( ) );
	}

	const_reference front( ) const {
		return *res;
	}

	const_reference back( ) const {
		return *( res + size( ) );
	}

	std::size_t size( ) const {
		return std::accumulate( dims.begin( ), dims.end( ), 1, [ ] ( std::size_t a, std::size_t b ) { return a * b; } );
	}

};

#include <vector>
#include <iostream>

template <typename TRange>
void array_print ( TRange&& range ) {
    for ( auto i : range ) { 
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

int main() {
    
    std::vector<double> dataz( 8, 0.0f );
    buffer_view<double> view8x1( dataz );
    buffer_view<double, 2> view2x4( dataz, 2, 4 );
    
    array_print( dataz );
    view8x1[0] = 2.0f;
    view8x1[1] = 2.0f;
    
    array_print( dataz );
    view2x4[{1, 1}] = 3.0f;
    view2x4[{1, 0}] = 3.0f;
    
    array_print( dataz );
    // calls will fail
    //buffer_view<double, 2> view2x4fail( dataz );
    //view2x4[ 1 ] = 50.0f;
}