#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <algorithm>

namespace Furrovine {

    template <typename T, std::size_t n, std::size_t a = std::alignment_of<T>::value>
	class fixed_vector {
	public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef pointer_type iterator;
		typedef const pointer_type const_iterator;

	private:
		typename std::aligned_storage<sizeof( T ) * n, a>::type items;
		std::size_t len;

		T* ptrat ( std::size_t idx ) {
			return static_cast<T*>( static_cast<void*>( &items ) ) + idx;
		}

		const T* ptrat( std::size_t idx ) const {
			return static_cast<const T*>( static_cast<const void*>( &items ) ) + idx;
		}

		T& refat ( std::size_t idx ) {
			return *ptrat( idx );
		}

		const T& refat ( std::size_t idx ) const {
			return *ptrat( idx );
		}

		void move_space_into( std::size_t idx ) {
			for ( std::size_t i = idx + 1; i < len; ++i ) {
				std::swap( refat( i - 1 ), refat( i ) );
			}
		}

		void free_space_at( std::true_type, std::size_t idx ) {
			for ( std::size_t i = len; i > idx; --i ) {
				refat( i ) = std::move( refat( i - 1 ) );
			}
		}

		void free_space_at( std::false_type, std::size_t idx ) {
			for ( std::size_t i = len; i > idx; --i ) {
				refat( i ) = refat( i - 1 );
			}
		}

		void prepare_insert( std::size_t idx ) {
			if ( idx >= len )
				throw std::out_of_range( "requested index is out of bounds" );
			if ( len == capacity( ) )
				throw std::out_of_range( "max capacity reached" );
			free_space_at( std::is_move_assignable<T>(), idx );
		}

	public:
		static const std::size_t max_size () {
			return n;
		}

		fixed_vector( ) : len( 0 ) {

		}

		fixed_vector( fixed_vector&& mov ) : len( 0 ) {
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( std::move( mov[ i ] ) );
			mov.clear( );
		}

		fixed_vector( const fixed_vector& mov ) : len( 0 ) {
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( mov[ i ] );
		}

		fixed_vector& operator=( fixed_vector&& mov ) {
			clear( );
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( std::move( mov[ i ] ) );
			mov.clear( );
			return *this;
		}

		fixed_vector& operator=( const fixed_vector& mov ) {
			clear( );
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( mov[ i ] );
			mov.clear( );
			return *this;
		}

		fixed_vector( std::size_t sz ) : len( std::min( n, sz ) ) {
			if ( sz > capacity( ) )
				throw std::out_of_range( "requested size is beyond fixed capacity" );
		}

		template <std::size_t c>
		fixed_vector( const T( &arr )[ c ] ) : len( c ) {
			static_assert( c < n, "Array too large to initialize fixed_vector" );
			std::copy( std::addressof( arr[ 0 ] ), std::addressof( arr[ c ] ), data( ) );
		}

		fixed_vector( std::initializer_list<T> initializer ) : len( std::min( n, initializer.size( ) ) ) {
			if ( initializer.size( ) > capacity( ) )
				throw std::out_of_range( "requested size is beyond fixed capacity" );
			std::copy( initializer.begin( ), initializer.begin( ) + len, data( ) );
		}

		bool empty () const {
			return len < 1;
		}

		bool not_empty () const {
			return len > 0;
		}

		bool full () const {
			return len >= n;
		}

		void push_back ( const T& item ) {
			if ( len == capacity( ) )
				throw std::out_of_range( "max capacity reached" );
			new( ptrat( len ) ) T( item );
			len++;
		}

		void push_back ( T&& item ) {
			if ( len == capacity( ) )
				throw std::out_of_range( "max capacity reached" );
			new( ptrat( len ) ) T( std::move( item ) );
			len++;
		}

		template <typename ...Tn>
		void emplace_back ( Tn&&... argn ) {
			if ( len == capacity( ) )
				throw std::out_of_range( "max capacity reached" );
			new( ptrat( len ) ) T( std::forward<Tn>( argn )... );
			len++;
		}

		void pop_back ( ) {
			if ( len == 0 )
				return;
			T& addr = refat( len - 1 );
			addr.~T();
			--len;
		}

		void clear () {
			for ( ; len > 0; ) {
				pop_back();
			}
		}

		void erase( std::size_t idx ) {
			if ( idx >= len )
				throw std::out_of_range( "requested index is out of bounds" );
			T& erased = refat( idx );
			erased.~T( );
			move_space_into( idx );
			--len;
		}

		void insert( std::size_t idx, const T& item ) {
			prepare_insert( idx );
			new( ptrat( idx ) ) T( item );
			len++;
		}

		void insert( std::size_t idx, T&& item ) {
			prepare_insert( idx );
			new( ptrat( idx ) ) T( std::move( item ) );
			len++;
		}

		template <typename... Tn>
		void emplace( std::size_t idx, Tn&&... argn ) {
			prepare_insert( idx );
			new( ptrat( idx ) ) T( std::forward<Tn>( argn )... );
			len++;
		}

		std::size_t size () const {
			return len;
		}

		std::size_t capacity () const {
			return n;
		}

		void resize ( std::size_t sz ) {
			if ( sz > capacity( ) )
				throw std::out_of_range( "requested size is beyond fixed capacity" );
			len = sz;
		}

		T* data () {
			return ptrat( 0 );
		}

		const T* data () const {
			return ptrat( 0 );
		}

		T& at ( std::size_t idx ) {
			if ( idx >= len )
				throw std::out_of_range( "requested index is out of bounds" );
			return refat( idx );
		}

		const T& at ( std::size_t idx ) const {
			if ( idx >= len )
				throw std::out_of_range( "requested index is out of bounds" );
			return refat( idx );
		}

		T& operator[] ( std::size_t idx ) {
			return refat( idx );
		}

		const T& operator[] ( std::size_t idx ) const {
			return refat( idx );
		}

		T& front () {
			return refat( 0 );
		}

		T& back () {
			return refat( len - 1 );
		}

		const T& front () const {
			return refat( 0 );
		}

		const T& back () const {
			return refat( len - 1 );
		}

		T* begin () {
			return data();
		}

		const T* cbegin () {
			return data();
		}

		const T* begin () const {
			return data();
		}

		const T* cbegin () const {
			return data();
		}

		T* end( ) {
			return data( ) + len;
		}

		const T* cend( ) {
			return data( ) + len;
		}

		const T* end( ) const {
			return data( ) + len;
		}

		const T* cend( ) const {
			return data( ) + len;
		}

		std::reverse_iterator<iterator> rbegin( ) {
			return std::reverse_iterator<iterator>( end( ) );
		}

		const std::reverse_iterator<iterator> crbegin( ) {
			return std::reverse_iterator<iterator>( cend( ) );
		}

		const std::reverse_iterator<iterator> rbegin( ) const {
			return std::reverse_iterator<iterator>( end( ) );
		}

		const std::reverse_iterator<iterator> crbegin( ) const {
			return std::reverse_iterator<iterator>( cend( ) );
		}

		std::reverse_iterator<iterator> rend( ) {
			return std::reverse_iterator<iterator>( begin( ) );
		}

		const std::reverse_iterator<iterator> crend( ) {
			return std::reverse_iterator<iterator>( cbegin( ) );
		}

		const std::reverse_iterator<iterator> rend( ) const {
			return std::reverse_iterator<iterator>( begin( ) );
		}

		const std::reverse_iterator<iterator> crend( ) const {
			return std::reverse_iterator<iterator>( cbegin() );
		}
	};

}

#include <iostream>

template <typename T, std::size_t n, std::size_t a>
void print ( Furrovine::fixed_vector<T, n, a>& fv ) {
    for ( auto& i : fv )
        std::cout << i << " ";
    std::cout << std::endl << std::endl;
}

int main( ) {
    using namespace Furrovine;
    
    fixed_vector<int, 5> fv = { 1, 2, 3, 4, 5 };
	fv.erase( 0 );
    print( fv );
    fv.emplace( 0, 10 );
	print( fv );
    fv.erase( 4 );
	print( fv );
    fv.insert( 0, 11 );
	print( fv );
    fv.erase( 2 );
	print( fv );
    fv.insert( 2, 12 );
    print( fv );
}