template <typename TIterator>
TIterator ReverseEncodeOneBytes( charcodepoint c, TIterator bytes ) const {
    //*bytes++ to get to the next one? Or *bytes-- ?
}

template <typename TIterator>
TIterator EncodeOneBytes( charcodepoint c, TIterator bytes ) const {
	if ( c <= 0x7F ) {
		*bytes++ = static_cast<byte>( c );
	}
	else if (c <= 0x7FF) {
		*bytes++ = static_cast<byte>( (c >> 6)            | 0xc0 ); /* 110x xxxx */
		*bytes++ = static_cast<byte>( (c          & 0x3f) | 0x80 ); /* 10xx xxxx */
	}
	else if (c <= 0xFFFF) {
		*bytes++ = static_cast<byte>(  (c >> 12)         | 0xe0 ); /* 1110 xxxx */
		*bytes++ = static_cast<byte>( ((c >>  6) & 0x3f) | 0x80 ); /* 10xx xxxx */
		*bytes++ = static_cast<byte>(  (c        & 0x3f) | 0x80 ); /* 10xx xxxx */
	}
	else if (c <= 0x1FFFFF) {
		*bytes++ = static_cast<byte>(  (c >> 18)         | 0xf0 ); /* 1111 0xxx */
		*bytes++ = static_cast<byte>( ((c >> 12) & 0x3f) | 0x80 ); /* 10xx xxxx */
		*bytes++ = static_cast<byte>( ((c >>  6) & 0x3f) | 0x80 ); /* 10xx xxxx */
		*bytes++ = static_cast<byte>( ( c        & 0x3f) | 0x80 ); /* 10xx xxxx */
	}
	/*else if (c <= 0x3FFFFFF) {
		*bytes++ = static_cast<byte>(  (c >> 24)         | 0xf8 ); // 1111 10xx 
		*bytes++ = static_cast<byte>( ((c >> 18) & 0x3f) | 0x80 ); // 10xx xxxx 
		*bytes++ = static_cast<byte>( ((c >> 12) & 0x3f) | 0x80 ); // 10xx xxxx 
		*bytes++ = static_cast<byte>( ((c >>  6) & 0x3f) | 0x80 ); // 10xx xxxx 
		*bytes++ = static_cast<byte>( ( c        & 0x3f) | 0x80 ); // 10xx xxxx 
	}
	else if (c <= 0x7FFFFFFF) {
		*bytes++ = static_cast<byte>(  (c >> 30)         | 0xfc ); // 1111 110x
		*bytes++ = static_cast<byte>( ((c >> 24) & 0x3f) | 0x80 ); // 10xx xxxx
		*bytes++ = static_cast<byte>( ((c >> 18) & 0x3f) | 0x80 ); // 10xx xxxx
		*bytes++ = static_cast<byte>( ((c >> 12) & 0x3f) | 0x80 ); // 10xx xxxx
		*bytes++ = static_cast<byte>( ((c >>  6) & 0x3f) | 0x80 ); // 10xx xxxx
		*bytes++ = static_cast<byte>( ( c        & 0x3f) | 0x80 ); // 10xx xxxx
	}*/
	else {
		/* Error Invalid Utf-8 */
		// TODO: encoding error
		return EncodeOneBytes( ReplacementCodePoint, bytes );	
	}
	return bytes;
}