#include <type_traits>

template <typename TAs, typename T, std::size_t n>
inline typename std::conditional<std::is_const<T>::value, const TAs, TAs>::type ( &array_cast( T( &array )[ n ] ) )[ ( n * sizeof( T ) ) / sizeof( TAs ) ] {
    using cast = typename std::conditional<std::is_const<T>::value, const TAs, TAs>::type[ ( n * sizeof( T ) ) / sizeof( TAs ) ];
	using pointer = typename std::conditional<std::is_const<T>::value, const void, void>::type;
	return *static_cast<cast*>( static_cast<pointer*>( &array ) );
}
        
int main( ) {
 
    

}

