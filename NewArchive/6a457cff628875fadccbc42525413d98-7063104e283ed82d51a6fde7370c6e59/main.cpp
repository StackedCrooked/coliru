#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>

template <typename T, std::size_t sz>
struct partial_array : std::array<T, sz> {
    std::size_t count;
};

typedef unsigned char byte;
typedef unsigned int charcodepoint;
typedef partial_array<byte, 8> maxcodeunit;

struct ascii {
    
    charcodepoint decode_one ( byte* data ) const {
        char* ascii = (char*)data;
        // ultra-lazy "decoding"
        charcodepoint result = *ascii;
        return result;
    }
    
    maxcodeunit encode_one ( charcodepoint codepoint ) const {
        maxcodeunit result;
        char* asciiresult = (char*)result.data();
        // Ultra-lazy "encoding"
        *asciiresult = (char)codepoint;
        result.count = 1;
        return result;
    }
    
};


// Allow for run-time switching
// of various encodings,
// giving a consistent interface for
// buffers and readers which have their
// encoding defined at run-time
struct TextEncoding {
    virtual charcodepoint decode_one ( byte* target ) const = 0;
    
    virtual maxcodeunit encode_one ( charcodepoint codepoint ) const = 0;
};

template <typename TEncoding>
struct TTextEncoding : TEncoding, TextEncoding {
    
    virtual charcodepoint decode_one ( byte* target ) const override {
        const TEncoding& tencoding = static_cast<const TEncoding&>( *this );
        return tencoding.decode_one( target );
    }
    
    virtual maxcodeunit encode_one ( charcodepoint codepoint ) const override {
        const TEncoding& tencoding = static_cast<const TEncoding&>( *this );
        return tencoding.encode_one( codepoint );
    }
    
};


int main() {
    // Yay, run-time polymorphism!
    std::unique_ptr<TextEncoding> encoding( new TTextEncoding<ascii>() );
    std::cout << encoding->decode_one( (byte*)"b" ) << '\n';
}
