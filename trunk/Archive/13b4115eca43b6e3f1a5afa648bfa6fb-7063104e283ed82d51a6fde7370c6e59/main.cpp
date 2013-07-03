#include <vector>
#include <iostream>

#include <type_traits>

    template <typename T, std::size_t n>
	class fixed_vector {
	private:
		typedef typename std::aligned_storage<sizeof( T ) * n>::type TStorage;
        TStorage items;
		std::size_t len;

		T* ptrat ( std::size_t idx ) {
    		return static_cast<T*>( static_cast<void*>( &items ) ) + idx;
		}

		const T* ptrat ( std::size_t idx ) const {
			return static_cast<const T*>( static_cast<const void*>( &items ) ) + idx;
		}

		T& refat ( std::size_t idx ) {
			return *ptrat( idx );
		}

		const T& refat ( std::size_t idx ) const {
			return *ptrat( idx );
		}

	public:
		fixed_vector( ) : len( 0 ) {

		}

		fixed_vector( std::size_t capacity ) : len( std::min( len, capacity ) ) {

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
			new( ptrat( len++ ) ) T( item );
		}

		void push_back ( T&& item ) {
			new( ptrat( len++ ) ) T( std::move( item ) );
		}

		template <typename ...Tn>
		void emplace_back ( Tn&&... argn ) {
			new( ptrat( len++ ) ) T( std::forward<Tn>( argn )... );
		}

		void pop_back ( ) {
			T& addr = refat( --len );
			addr.~T();
		}

		void clear () {
			for ( ; len > 0; ) {
				pop_back();
			}
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

		std::size_t size () const {
			return len;
		}

		std::size_t capacity () const {
			return n;
		}

		T* data () {
			return ptrat( 0 );
		}

		const T* data () const {
			return ptrat( 0 );
		}

		const T& operator[] ( std::size_t idx ) const {
			return refat( idx );
		}

		T& operator[] ( std::size_t idx ) {
			return refat( idx );
		}

		T* begin () {
			return data();
		}

		const T* cbegin () {
			return data();
		}

		T* begin () const {
			return data();
		}

		const T* cbegin () const {
			return data();
		}

		T* end () {
			return data() + len;
		}

		const T* cend () {
			return data() + len;
		}

		T* end () const {
			return data() + len;
		}

		const T* cend () const {
			return data() + len;
		}
	};

int main () {
    fixed_vector<int, 8> arf;
    arf.push_back( 1 );
    std::cout << arf.front() << " ... " << arf.back() << '\n';
    arf.emplace_back( 2 );
    std::cout << arf.front() << " ... " << arf.back() << '\n';
    arf.emplace_back( 3 );
    std::cout << arf.front() << " ... " << arf.back() << '\n';
}