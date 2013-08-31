#include <vector>
#include <iostream>

template <typename ...Args>
static StringBase Format ( const StringBase& format, const Args&... args ) {
	StringBase value;
	if ( sizeof...(args) < 1 ) {
		return format;
	}

	charcodepoint c = 0;
	ulword index = 0;
	ulword start = 0;
	
	value.Reserve( format.Length() * 3 );
	auto i = format.begin();
	
	while ( i != format.end() ) {
		c = *i;
		
		if ( c != '{' ) {
			value.Append( c );
			++i;
			continue;
		}

		auto cbegin = i;

		++i;

		index = 0;
		c = *i;
		while ( i != format.end() && c >= '0' && c <= '9' ) {
			index *= 10;
			index += c - '0';
			++i;
			c = *i;
		}
		

		auto cend = i;
		if ( c != '}' ) {
			while ( cbegin != cend ) {
				value.Append( *cbegin );
				++cbegin;
			}
			continue;
		}

		++i;
		
		if ( sizeof...( args ) > index ) {
			Format<0, Args... >( value, index, args... );
		}
	}
	return value;
}

template <ulword n, typename T, typename ... Args>
static void Format ( StringBase& value, ulword index, const T& arg0, const Args&... args ) {
	if ( index == n ) {
		FormatSelected( value, arg0 );
	}
	else if ( n < sizeof...( args ) + n ) {
		Format<n + 1, Args...>( value, index, args... );
	}
}

template <ulword n, typename ... Args>
static void Format ( StringBase& value, ulword index ) {
	
}

template <typename T>
static void FormatSelected ( StringBase& value, const T& arg0 ) {
	FormatSelected( value, static_cast<const StringBase&>( arg0 ) );
}

static void FormatSelected ( StringBase& value, const StringBase& arg0 ) {
	value.codeunitstorage.append( arg0.codeunitstorage.begin(), arg0.codeunitstorage.end() );
}

int main () {
    
}