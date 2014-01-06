#include <iostream>

#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <algorithm>

typedef unsigned char byte;

template <typename T, std::size_t n>
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
	typename std::aligned_storage<sizeof( T ) * n>::type items;
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

public:
	static const std::size_t max_size () {
		return n;
	}

	fixed_vector( ) : len( 0 ) {

	}

	fixed_vector( std::size_t capacity ) : len( std::min( n, capacity ) ) {

	}

	template <std::size_t c>
	fixed_vector( T( &arr )[ c ] ) : len( c ) {
        static_assert( c < n, "Array too large to initialize fixed_vector" );
		std::copy( std::addressof( arr[0] ), std::addressof( arr[c] ), data( ) );
	}

	fixed_vector( std::initializer_list<T> initializer ) : len( std::min( n, initializer.size( ) ) ) {
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

	std::size_t size () const {
		return len;
	}

	std::size_t capacity () const {
		return n;
	}

	void resize ( std::size_t sz ) {
		len = std::min( sz, n );
	}

	T* data () {
		return ptrat( 0 );
	}

	const T* data () const {
		return ptrat( 0 );
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

	T* end () {
		return data() + len;
	}

	const T* cend () {
		return data() + len;
	}

	const T* end () const {
		return data() + len;
	}

	const T* cend () const {
		return data() + len;
	}
};

template <typename TIter1, typename TIter2, typename TPred>
bool subsequence_equals( TIter1 biter1, TIter1 eiter1, TIter2 biter2, TIter2 eiter2, TPred&& predicate ) {
    while ( biter1 != eiter1 && biter2 != eiter2 ) {
		if ( !predicate( *biter1, *biter2 ) ) {
			return false;
		}
		++biter1;
		++biter2;
	}
	return true;
}

template <typename TIter1, typename TIter2>
bool subsequence_equals( TIter1 biter1, TIter1 eiter1, TIter2 biter2, TIter2 eiter2 ) {
	typedef typename std::add_const<decltype( *biter1 )>::type ref1_t;
	typedef typename std::add_const<decltype( *biter2 )>::type ref2_t;
	return subsequence_equals( biter1, eiter1, biter2, eiter2, [ ] ( ref1_t a, ref2_t b ) { return a == b; } );
}

template <typename TCont1, typename TCont2>
bool subsequence_equals( TCont1&& cont1, TCont2&& cont2 ) {
    return subsequence_equals( std::begin( cont1 ), std::end( cont1 ), std::begin( cont2 ), std::end( cont2 ) );
}

template <typename TCont1, typename TCont2, typename TPred>
bool subsequence_equals( TCont1&& cont1, TCont2&& cont2, TPred&& pred ) {
	return subsequence_equals( std::begin( cont1 ), std::end( cont1 ), std::begin( cont2 ), std::end( cont2 ), std::forward<TPred>( pred ) );
}

template <class T, class... Tn>
std::array<T, 1 + sizeof...( Tn )> make_array( T&& head, Tn&&... values ) {
	return{ std::forward<T>( head ), std::forward<Tn>( values )... };
}

enum class MagicIdentity {
	Unknown,
	Wave,
	Flac,
	Vorbis,
	Ogg,

	Autodesk3DS,
	X,
	MDX,
	MD2,
	MD3,
	OBJ,
	MTL,
	FBX,

	XNB,
	
	Utf7,
	Utf8,
	Utf16,
	Utf32,

	JPG,
	JPEG,
	BMP,
	GIF,
	PNG,
	DDS,
	TGA,
	PPM,
	ICO,
	CUR,
	PCX,
	ANI,

	HLSLSource,
	GLSLSource,
	HLSLBytecode,
};

struct magic {
	fixed_vector<byte, 16> data;
	MagicIdentity identity;
};

template <typename TAs, typename T, std::size_t n>
inline typename std::conditional<std::is_const<T>::value, const TAs, TAs>::type ( &array_cast( T( &array )[ n ] ) )[ ( n * sizeof( T ) ) / sizeof( TAs ) ] {
	typedef typename std::conditional<std::is_const<T>::value, const TAs, TAs>::type cast[ ( n * sizeof( T ) ) / sizeof( TAs ) ];
	typedef typename std::conditional<std::is_const<T>::value, const void, void>::type pointer;
	return *static_cast<cast*>( static_cast<pointer*>( &array ) );
}

int main () {
    auto magics = make_array(
        magic{ { (byte)0x38, (byte)0x2B, (byte)0x2F, (byte)0x76 }, MagicIdentity::Utf7 },
        magic{ { (byte)0x38, (byte)0x2B, (byte)0x2F, (byte)0x76 }, MagicIdentity::Utf7 },
        magic{ { (byte)0x39, (byte)0x2B, (byte)0x2F, (byte)0x76 }, MagicIdentity::Utf7 },
        magic{ { (byte)0x2B, (byte)0x2B, (byte)0x2F, (byte)0x76 }, MagicIdentity::Utf7 },
        magic{ { (byte)0x2F, (byte)0x2B, (byte)0x2F, (byte)0x76 }, MagicIdentity::Utf7 },
        magic{ { (byte)0xBF, (byte)0xEF, (byte)0xBB }, MagicIdentity::Utf8 },
        magic{ { (byte)0xFF, (byte)0xFE }, MagicIdentity::Utf16 },
        magic{ { (byte)0xFF, (byte)0xFE }, MagicIdentity::Utf16 },
        magic{ { (byte)0xFE, (byte)0xFF }, MagicIdentity::Utf16 },
        magic{ { (byte)0, (byte)0xFF, (byte)0xFE, (byte)0 }, MagicIdentity::Utf32 },
        magic{ { (byte)0, (byte)0xFF, (byte)0xFE, (byte)0 }, MagicIdentity::Utf32 },
        magic{ { (byte)0xFF, (byte)0, (byte)0, (byte)0xFE }, MagicIdentity::Utf32 },
        magic{ { (byte)'D', (byte)'D', (byte)'S', (byte)' ' }, MagicIdentity::DDS },
        magic{ { (byte)0x89, (byte)'P', (byte)'N', (byte)'G' }, MagicIdentity::PNG },
        magic{ { (byte)0xD8, (byte)0xFF }, MagicIdentity::JPEG },
        magic{ { (byte)0xD8, (byte)0xFF }, MagicIdentity::JPG },
        magic{ { (byte)0x0, (byte)0, (byte)0, (byte)0x1 }, MagicIdentity::ICO },
        magic{ { (byte)0x0, (byte)0, (byte)0, (byte)0x2 }, MagicIdentity::CUR },
        magic{ { (byte)'R', (byte)'I', (byte)'F', (byte)'F' }, MagicIdentity::ANI },
        magic{ { (byte)'P', (byte)'3' }, MagicIdentity::PPM },
        magic{ { (byte)'P', (byte)'2' }, MagicIdentity::PPM },
        magic{ { (byte)'P', (byte)'1' }, MagicIdentity::PPM },
        magic{ { (byte)'P', (byte)'6' }, MagicIdentity::PPM },
        magic{ { (byte)'P', (byte)'5' }, MagicIdentity::PPM },
        magic{ { (byte)'P', (byte)'4' }, MagicIdentity::PPM },
        magic{ { (byte)'B', (byte)'M' }, MagicIdentity::BMP },
        magic{ { (byte)10 }, MagicIdentity::PCX },
        magic{ { (byte)'G', (byte)'I', (byte)'F', (byte)'8', (byte)'7', (byte)'a' }, MagicIdentity::GIF },
        magic{ { (byte)'G', (byte)'I', (byte)'F', (byte)'8', (byte)'9', (byte)'a' }, MagicIdentity::GIF },
        magic{ { (byte)'4', (byte)'D', (byte)'4', (byte)'D' }, MagicIdentity::Autodesk3DS },
        magic{ { (byte)'I', (byte)'D', (byte)'P', (byte)'2' }, MagicIdentity::MD2 },
        magic{ { (byte)'I', (byte)'D', (byte)'P', (byte)'3' }, MagicIdentity::MD3 },
        magic{ { (byte)0x2E, (byte)0x58, (byte)0x44, (byte)0x4D }, MagicIdentity::MDX },
        magic{ { (byte)'x', (byte)'o', (byte)'f', (byte)' ' }, MagicIdentity::X },
        magic{ { (byte)'K', (byte)'a', (byte)'y', (byte)'d', (byte)'a', (byte)'r', (byte)'a' }, MagicIdentity::FBX },
        magic{ { (byte)'R', (byte)'I', (byte)'F', (byte)'F' }, MagicIdentity::Wave },
        magic{ { (byte)0x43, (byte)0x66, (byte)0x4C, (byte)0x61 }, MagicIdentity::Flac },
        magic{ { (byte)'O', (byte)'g', (byte)'g', (byte)'S' }, MagicIdentity::Ogg },
        magic{ { (byte)0x73, (byte)0x01, (byte)0x76, (byte)0x6f, (byte)0x72, (byte)0x62, (byte)0x69 }, MagicIdentity::Vorbis },
        magic{ { (byte)'X', (byte)'N', (byte)'B', (byte)'w' }, MagicIdentity::XNB },
        magic{ { (byte)'X', (byte)'N', (byte)'B', (byte)'m' }, MagicIdentity::XNB },
        magic{ { (byte)'X', (byte)'N', (byte)'B', (byte)'x' }, MagicIdentity::XNB }
    );

    char cxnbw[] = "XNBw";
    fixed_vector<byte, 16> bytes( array_cast<byte>( cxnbw ) );
    
    auto target = std::find_if( magics.begin(), magics.end(),
        [ &bytes ]( const magic& m ) { return subsequence_equals( bytes, m.data ); } 
    );
    if ( target == magics.end() ) {
        std::cout << "Did not find XNBw..." << std::endl;
    }
    else { 
        std::cout << "Found XNBw!" << std::endl;
    }
}

