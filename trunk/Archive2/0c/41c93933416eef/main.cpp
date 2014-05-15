// https://software.intel.com/en-us/articles/xml-parsing-accelerator-with-intel-streaming-simd-extensions-4-intel-sse4

#include "nmmintrin.h" 
#include "emmintrin.h" 

#define STTNISTRLENLIMIT 4 
char* yylim;
char* yycur;
#define YYSWITCHBUFFER yycur += 16; yylim += 16

void checkIncompleteBytes(unsigned int& mask, unsigned int& tmask, int& length, unsigned int num);
bool recogUnicodeRange(const __m128i data, int& dataLength, unsigned int mask);

struct SAX2Processor {
    void newLine( char * data ) {}
    void reportCharDataContent( char *yycur, unsigned int passLen) {}
};

void scanCharDataContentwithSTTNI(SAX2Processor* saxProcessor) { 
    unsigned int length = yylim - yycur; 
    unsigned char* data = (unsigned char*)yycur; 
    if( *data == '<' || *data == '&' || *data == ']') return; 
    unsigned int dataLen = 0; 
    // initialize the one byte encoding rule and nonCharaData rule 
    const __m128i asciiCharData = _mm_set_epi8(0,0,0,0,0,0,0x7F,0x5E,0x5C,0x3D, 0x3B,0x27,0x25,0x20,0,0); 
    const __m128i nonCharData = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0x5D,0x3C,0x26,0x0D,0x0A); 

    do { 
        // special new line processing for ‘x0A’,‘x0D’ 
        if( *data == '\0' ) { 
            saxProcessor->newLine((char*)data); 
            data++; length--; 
        } else if(*data == '\0') { 
            saxProcessor->newLine((char*)data); 
            if( *(data+1) == '\0' ) { 
                data += 2; length -= 2; yycur++; 
            } else { 
                *data = '\0'; data++; length--; 
            } 
        }

        while( length > 0 ) { 
            if( length >= 16 ) dataLen = 16; 
            else dataLen = length; 
            const __m128i mData = _mm_loadu_si128((__m128i*)data); 
            // locate the Character Data part with the nonCharaData characters 
            int index = _mm_cmpestri(nonCharData, 5, mData, dataLen, _SIDD_CMP_EQUAL_ANY); 
            if( index == 0 ) break;
            if( index > dataLen ) index = dataLen; 
            bool shouldBreak = index < dataLen ? true : false; 
            // check the one byte encoding rule(ASCII) 
            unsigned int mask = _mm_cvtsi128_si32(_mm_cmpestrm(asciiCharData, 10, 
                mData, index, _SIDD_CMP_RANGES|_SIDD_MASKED_NEGATIVE_POLARITY)); 
            // if not all hit ASCII, continue to check other Unicode rules 
            if( mask == 0 || recogUnicodeRange(mData, index, ~mask)) { 
                data += index; 
                length -= index; 
                if( shouldBreak ) break;
            } else { 
                break;
            } 
        }

        unsigned int passLen = (char*)data - yycur; 
        if( passLen == 0 ) break; 
        // report Character Data to user 
        saxProcessor->reportCharDataContent(yycur, passLen); 
        yycur += passLen; 
        YYSWITCHBUFFER; 
    } while( length >= STTNISTRLENLIMIT && (*data == '\0' || *data == '\0') ); 
} 


bool recogUnicodeRange(const __m128i data, int& dataLength, unsigned int mask) {
    //first check whether in the 2 bytes encoding range 
    const __m128i Unicode_80_BE = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\xBE','\x80');
    unsigned int mask_80_BE = _mm_cvtsi128_si32(_mm_cmpestrm(Unicode_80_BE, 2, data, dataLength, _SIDD_CMP_RANGES));
    const __m128i Unicode_C2_DF = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\xDF', '\xC2');
    unsigned int mask_C2_DF = _mm_cvtsi128_si32(_mm_cmpestrm(Unicode_C2_DF, 2, data, dataLength, _SIDD_CMP_RANGES));
    if( mask_C2_DF > 0 ) {
        checkIncompleteBytes(mask_C2_DF, mask, dataLength, 1);
        if( mask_C2_DF > 0 ) { 
            unsigned int mask_C2_DF_2 = mask_C2_DF << 1;
            if( (mask_C2_DF_2 & mask_80_BE) != mask_C2_DF_2 ) {
                const __m128i Unicode_80_BF = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\xBF', '\x80');
                unsigned int mask_80_BF = _mm_cvtsi128_si32(_mm_cmpestrm(Unicode_80_BF, 2, data, dataLength, _SIDD_CMP_RANGES)); 
                if( (mask_C2_DF_2 & mask_80_BF) != mask_C2_DF_2 ) { 
                    return false; 
                }
            }
            mask |= mask_C2_DF;
            mask |= mask_C2_DF_2;
            if( mask == 0xFFFFFFFF ) { 
                return true;
            }
        } else {
            if( dataLength <= 0 ) return false; 
            if( mask == 0xFFFFFFFF ) return true; 
        }
    }

    //then check whether in the 3 bytes encoding range 
    const __m128i Unicode_E1_EC_EE_EF = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\xEF', '\xEF', '\xEE', '\xEE', '\xEC', '\xE1'); 
    unsigned int mask_E1_EC_EE_EF = _mm_cvtsi128_si32(_mm_cmpestrm(Unicode_E1_EC_EE_EF, 6, data, dataLength, _SIDD_CMP_RANGES));
    if( mask_E1_EC_EE_EF > 0 ) {
        checkIncompleteBytes(mask_E1_EC_EE_EF, mask, dataLength, 2); 
        if( mask_E1_EC_EE_EF > 0 ) { 
            unsigned int mask_E1_EC_EE_EF_2 = mask_E1_EC_EE_EF << 1; 
            unsigned int mask_E1_EC_EE_EF_3 = mask_E1_EC_EE_EF << 2; 
            if( (mask_E1_EC_EE_EF_2 & mask_80_BE) == mask_E1_EC_EE_EF_2 ) { 
                if( (mask_E1_EC_EE_EF_3 & mask_80_BE) != mask_E1_EC_EE_EF_3 ) { 
                    const __m128i Unicode_80_BF = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\xBF', '\x80'); 
                    unsigned int mask_80_BF = _mm_cvtsi128_si32(_mm_cmpestrm(Unicode_80_BF, 2, data, dataLength, _SIDD_CMP_RANGES));
                    if( (mask_E1_EC_EE_EF_3 & mask_80_BF) != mask_E1_EC_EE_EF_3 ) { 
                        return false;
                    }
                }
                mask |= mask_E1_EC_EE_EF;
                mask |= mask_E1_EC_EE_EF_2;
                mask |= mask_E1_EC_EE_EF_3;
                if( mask == 0xFFFFFFFF ) { 
                    return true;
                }
            } else {
                return false;
            }
        } else {
            if( dataLength <= 0 ) return false;
            if( mask == 0xFFFFFFFF ) return true;
        }
    }
    return false;
}

inline void checkIncompleteBytes(unsigned int& mask, unsigned int& tmask, int& length, unsigned int num) { 
    for(unsigned int i = num; i > 0; i--) {
        if( (mask & (1<<(length-i))) > 0 ) {
            for(unsigned int j = i; j > 0; j--) {
                mask &= ~(1<<length-j); 
                tmask |= (1<<length-j);
            }
            length -= i;
            break;
        }
    }
}

int main() { return 0; }
