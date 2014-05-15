#include <iostream>
#include <nmmintrin.h>
#include <emmintrin.h>
#include <algorithm>
#include <cstdint>
#include <string>
using std::cout;
using std::endl;
using std::string;

typedef uint8_t byte;
const int mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_BIT_MASK;

static __m128i broadcast_u8( byte b ) {
    byte m128i_u8[16];
    std::fill_n(m128i_u8, 16, b);
    uint64_t *m128i_u64 = reinterpret_cast<uint64_t *>( m128i_u8 );
    return _mm_set_epi64x( m128i_u64[1], m128i_u64[0] );
}

uint seqRank( const uint *vector, byte searchedByte, size_t position )
{
    size_t d = position >> 4, r = position & 0xf;
    size_t count = 0;
    __m128i window, returnValue;
    __m128i patt = broadcast_u8( searchedByte );

    const uint64_t * text_array = reinterpret_cast<const uint64_t *>( vector );
    for (size_t i=0; i < d; ++i) {
        window = _mm_set_epi64x( text_array[1] , text_array[0] );
        returnValue = _mm_cmpestrm( patt, 16, window, 16, mode );
        count += _mm_popcnt_u32( _mm_extract_epi32(returnValue,0) );
        text_array += 2;
    }

    window = _mm_set_epi64x( text_array[1], text_array[0] );
    returnValue = _mm_cmpestrm( patt, r, window, r, mode );
    count += _mm_popcnt_u32( _mm_extract_epi32(returnValue,0) ) + r - 16;
    
    return count;
}

int main() {
    string haystack = "The quick brown fox jumps over the lazy dog.";
    byte needle = 'o';
    const uint* h = reinterpret_cast<const uint *>( haystack.c_str() );
    cout << "There are " << seqRank( h, needle, 14 ) << " occurrences of " << char(needle) << " in " << haystack << endl;
    return 0;
}