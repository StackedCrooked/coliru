# include "nmmintrin.h"
# include <emmintrin.h>

typedef unsigned char byte;
const int mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_BIT_MASK ;

uint seqRank ( uint * vector , byte searchedByte , uint position ){
    register uint i , cont = 0;
    __m128i patt , window , returnValue ;
    byte * c1 , patt_code [16];
    uint d = position >> 4 , r = position & 0xf ;
    for ( i =0; i <16; i ++)
        patt_code [i ]= searchedByte ;
    long long * pat_array = ( long long *) patt_code ;
    patt = _mm_set_epi64x ( pat_array [1] , pat_array [0]) ;
    long long * text_array = ( long long *) vector ;
    for ( i =0; i <d; i ++) {
        window = _mm_set_epi64x ( text_array [1] , text_array [0]) ;
        returnValue = _mm_cmpestrm ( patt , 16 , window , 16 , mode ) ;
        cont += _mm_popcnt_u32 ( _mm_extract_epi32 ( returnValue ,0) );
        text_array += 2;
    }
    window = _mm_set_epi64x ( text_array [1] , text_array [0]) ;
    returnValue = _mm_cmpestrm ( patt , r , window , r , mode );
    cont += _mm_popcnt_u32 ( _mm_extract_epi32 ( returnValue ,0) ) +r -16;
    return cont ;
}

int main() { return 0; }