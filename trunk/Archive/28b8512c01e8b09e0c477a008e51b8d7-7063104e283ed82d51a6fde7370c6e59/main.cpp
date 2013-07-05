template <typename TChar16, typename TEndian>
struct TUtf16TextEncoding : public TextEncodingUnit<TChar16, 2> {
public:
	using TextEncodingUnit::EncodeOne;
	using TextEncodingUnit::DecodeOne;

	template <typename TIterator>
	TIterator DecodeOne ( TIterator bytes, charcodepoint& c ) const {
		c = 0;
		charcodepoint c2 = 0;
		c = *bytes++;
		c |= ( *bytes++ ) << 8;

		if ( c >= 0xD800 && c <= 0xDBFF ) {
			c2 = *bytes++;
			c2 |= ( *bytes ) << 8;
			if ( c2 >= 0xDC00 && c2 <= 0xDFFF ) {
				c = ( (c - 0xD800) << 10)
					+ (c2 - 0xDC00) + 0x00010000;
				++bytes;
			}
			else {
				--bytes;
			}
		}

		c = TEndian::Value( c );

		return bytes;
	}

	template <typename TIterator>
	TIterator EncodeOne ( charcodepoint c, TIterator bytes ) const {
		union {
			struct {
				uint16 uint160;
				uint16 uint161;
			};
			uint8 uint8s[4];
		} u16c;

		byte* u16cb = &u16c.uint8s[0];

		if ( c < 0xFFFF ) {
			u16c.UInt160 = (uint16)TEndian::Value( (uint16)c );
			*bytes++ = *u16cb++;
			*bytes++ = *u16cb;
		}
		else if ( c < 0x110000 ) {
			c -= 0x00010000;
			u16c.UInt160 = (charutf16)( ( c >> 10 ) + 0xD800 );
			u16c.UInt161 = (charutf16)( ( c & 0x03FF ) + 0xDC00 );
			u16c.UInt160 = TEndian::Value( u16c.UInt160 );
			u16c.UInt161 = TEndian::Value( u16c.UInt161 );
			*bytes++ = *u16cb++;
			*bytes++ = *u16cb++;
			*bytes++ = *u16cb++;
			*bytes++ = *u16cb;
		}
		else {
			// TODO: Encoding throw
			return EncodeOne( ReplacementCodePoint, bytes );	
		}

		return bytes;
	}
}
    
int main () {
    
}