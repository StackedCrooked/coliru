#include <iostream>
#include <string>
#include <vector>
#include <cstring>

const auto null = nullptr;

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
		auto get_data( std::false_type, T&& cont ) -> decltype( cont.data( ) ) {
			return cont.data( );
		}

		template <typename T>
		auto get_size( std::false_type, T&& cont ) -> decltype( cont.size( ) ) {
			return cont.size( );
		}

		template <typename T, std::size_t n>
		T* get_data( std::true_type, T( &cont )[ n ] ) {
			return std::addressof( cont[ 0 ] );
		}

		template <typename T, std::size_t n>
		std::size_t get_size( std::true_type, T( &cont )[ n ] ) {
			return n;
		}

		template <typename T>
		auto get_data( T&& cont ) -> decltype( get_data( std::is_array<T>( ), std::forward<T>( cont ) ) ) {
			return get_data( std::is_array<T>(), std::forward<T>( cont ) );
		}

		template <typename T>
		auto get_size( T&& cont ) -> decltype( get_size( std::is_array<T>( ), std::forward<T>( cont ) ) ) {
			return get_size( std::is_array<T>( ), std::forward<T>( cont ) );
		}
	}

    template <typename T>
    class buffer_view {
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
		T* res;
		std::size_t sz;

	public:

		buffer_view( ) : res( nullptr ), sz( 0 ) {

		}

		buffer_view( T* buffer, std::size_t n )
			: res( buffer ), sz( n ) {

		}

		template<std::size_t n>
		buffer_view( T( &array )[ n ] ) : buffer_view( std::addressof( array[ 0 ] ), n ) {

		}

		template <typename TContainer>
		buffer_view( TContainer&& container ) : buffer_view( detail::get_data( container ), detail::get_size( container ) ) {

		}

		bool is_null( ) const {
			return res == null;
		}

		bool empty( ) const {
			return sz < 1;
		}

		bool not_empty( ) const {
			return sz > 0;
		}

		T* begin( ) {
			return res;
		}

		T* end( ) {
			return res + sz;
		}

		const T* begin( ) const {
			return res;
		}

		const T* end( ) const {
			return res + sz;
		}

		const T* cbegin( ) {
			return res;
		}

		const T* cend( ) {
			return res + sz;
		}

		const T* cbegin( ) const {
			return res;
		}

		const T* cend( ) const {
			return res + sz;
		}

		T& operator[] ( std::size_t i ) {
			return res[ i ];
		}

		const T& operator[] ( std::size_t i ) const {
			return res[ i ];
		}

		T* data( ) {
			return res;
		}

		const T* data( ) const {
			return res;
		}

		reference front( ) {
			return *res;
		}

		reference back( ) {
			return *( res + sz );
		}

		const_reference front( ) const {
			return *res;
		}

		const_reference back( ) const {
			return *( res + sz );
		}

		T*& data_ref( ) {
			return res;
		}

		const T*& data_ref( ) const {
			return res;
		}

		std::size_t& size_ref( ) {
			return sz;
		}

		const std::size_t& size_ref( ) const {
			return sz;
		}

		std::size_t size( ) const {
			return sz;
		}
	};

int main()
{
    int titties[2] = { 1, 2 };
    std::vector<int> balls = {3, 4};
    // Properly gets size and data
    buffer_view<int> titties_view = titties;
    buffer_view<int> balls_view = balls;
    std::cout << "Titties: " << std::endl;
    std::cout << titties_view.size() << std::endl;
    std::cout << titties_view[0] << std::endl;
    std::cout << "Balls: " << std::endl;
    std::cout << balls_view.size() << std::endl;
    std::cout << balls_view[0] << std::endl;
}
