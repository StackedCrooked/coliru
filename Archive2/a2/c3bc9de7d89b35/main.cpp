#include <type_traits>

template <typename TAs, typename T, ulword n>
inline typename std::conditional<std::is_const<T>::value, const TAs, TAs>::type ( &array_cast( T( &array )[ n ] ) )[ ( n * sizeof( T ) ) / sizeof( TAs ) ] {
    typedef typename std::conditional<std::is_const<T>::value, const TAs, TAs>::type cast[ ( n * sizeof( T ) ) / sizeof( TAs ) ];
	typedef typename std::conditional<std::is_const<T>::value, const void, void>::type pointer;
	return *static_cast<cast*>( static_cast<pointer*>( &array ) );
}
        
int main( ) {
 
    

}

