template <typename TIterator>
TIterator DecodeOne ( TIterator bytes, charcodepoint& c ) const {
	uint16 c0, c1;
	
	c0 = *bytes++;
	c0 |= ( *bytes++ ) << 8;
	c = TEndian::Value( c0 );

	if ( c0 >= 0xD800 && c0 <= 0xDBFF ) {
		c1 = *bytes++;
		c1 |= ( *bytes ) << 8;
		if ( c1 >= 0xDC00 && c1 <= 0xDFFF ) {
			c1 = TEndian::Value( c1 );
			c = ( (c - 0xD800) << 10)
				+ (c1 - 0xDC00) + 0x00010000;
			++bytes;
		}
		else {
			// TODO: decoder error
			--bytes;
		}
	}

	
	return bytes;
}
    
int main () {
    
}