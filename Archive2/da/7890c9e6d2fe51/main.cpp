#include <immintrin.h>
#include <stdio.h>

int main() {
    int x = 0x87654321;
	
	unsigned char mask1a[32] = {
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
        0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02,
		0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03,
	};
 
    unsigned char mask2a[16] = {
		0x01, 0x02, 0x04, 0x08,
		0x10, 0x20, 0x40, 0x80,
		0x01, 0x02, 0x04, 0x08,
		0x10, 0x20, 0x40, 0x80,
	};

    __m128i y = _mm_set1_epi32(x);
	__m128i mask_low  = _mm_loadu_si128((__m128i*)&mask1a[ 0]);
    __m128i mask_high = _mm_loadu_si128((__m128i*)&mask1a[16]);
	__m128i z_low  = _mm_shuffle_epi8(y,mask_low);
    __m128i z_high = _mm_shuffle_epi8(y,mask_high);

    char out[32];
	_mm_storeu_si128((__m128i*)out,z_low);
	for(int i=0; i<16; i++) printf("%x ", out[i]); printf("\n");
    _mm_storeu_si128((__m128i*)out,z_high);
	for(int i=0; i<16; i++) printf("%x ", out[i]); printf("\n");
	__m128i mask2 = _mm_loadu_si128((__m128i*)mask2a);
	z_low  = _mm_and_si128(z_low,mask2);
    z_high = _mm_and_si128(z_high,mask2);

    _mm_storeu_si128((__m128i*)out,z_low);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {		
			printf("%x ", out[4*i+j]); 
		}printf("\n");
	} printf("\n");

    _mm_storeu_si128((__m128i*)out,z_high);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {		
			printf("%x ", out[4*i+j]); 
		}printf("\n");
	} printf("\n");
}