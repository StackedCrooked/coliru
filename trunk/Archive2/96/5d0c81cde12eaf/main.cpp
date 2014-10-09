#include <iostream>
#include <algorithm>
#include <iterator>

enum type { REG_SZ, REG_EXPAND_SZ, REG_MULTI_SZ } ; // dummy values

// compute the byte size including the string null terminator(s) of lpData
template < typename C > bool print_byte_size( const C* lpData, std::size_t n, type dwType )
{
    std::size_t nchars ;
    std::ptrdiff_t data_size_in_bytes ;

    switch(dwType)
    {
        case REG_SZ:
        case REG_EXPAND_SZ:
            nchars = std::find( lpData, lpData+n, 0 ) - lpData ;
            data_size_in_bytes = ( nchars + 1 ) * sizeof(C) ;
            break ;

        case REG_MULTI_SZ:
            nchars = std::adjacent_find( lpData, lpData+n, []( C a, C b ) { return !a && !b ; } ) - lpData ;
            data_size_in_bytes = ( nchars + 2 ) * sizeof(C) ;
            break ;

        default: return false ;
	}

	return std::cout << data_size_in_bytes << ' ' ;
}

// compute the byte size including the string null terminator(s) of lpData
template < typename C > bool print_byte_size2( const C* lpData, type dwType )
{
    auto p = lpData ;
	switch(dwType)
	{
        case REG_SZ:
        case REG_EXPAND_SZ:
            while( *p++ ) ;
            break ;

        case REG_MULTI_SZ:
            while( *p++ || *p++ ) ;
            break ;

        default: return false ;
	}

	std::ptrdiff_t data_size_in_bytes = ( p - lpData ) * sizeof(*lpData) ;
	return std::cout << data_size_in_bytes << ' ' ;
}

template < typename STR > void test( const STR& str )
{
    std::cout << "size of each character is " << sizeof(*str) << " : " ;
    print_byte_size( str, sizeof(str), REG_SZ ) ;
    print_byte_size2( str, REG_SZ ) ;

    print_byte_size( str, sizeof(str), REG_MULTI_SZ ) ;
    print_byte_size2( str, REG_MULTI_SZ ) ;
    std::cout << '\n' ;
}

int main()
{
    const char str[] = "abcdefgh\0ijk\0lmn\0opqr\0stuv\0wxyz\0\0!!!!" ;
    test(str) ;
    
    const char16_t str16[] = u"abcdefgh\0ijk\0lmn\0opqr\0stuv\0wxyz\0\0!!!!" ;
    test(str16) ;

    const wchar_t wstr[] = L"abcdefgh\0ijk\0lmn\0opqr\0stuv\0wxyz\0\0!!!!" ;
    test(wstr) ;

    const char32_t str32[] = U"abcdefgh\0ijk\0lmn\0opqr\0stuv\0wxyz\0\0!!!!" ;
    test(str32) ;
}
