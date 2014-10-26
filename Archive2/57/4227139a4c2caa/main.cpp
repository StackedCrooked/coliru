#include <algorithm>
#include <memory>
#include <functional>

// templates:
//    contains, std::less, std::count, std::begin, std::end, std::minus, std::plus,
//    std::addressof, std::cref,  std::reference_wrapper::get
//
// nested eight levels deep
//    1. contains 2. less 3. count 4. minus 5. plus 6. addressof 7. cref 8. get
template < typename T, std::size_t N > bool contains(  const T(&a)[N], const T& v )
{
    return std::less<T>() ( std::count( std::begin(a), std::end(a),
                                        std::minus<T>()( std::plus<T>() (
                                                                           *std::addressof( std::cref(v).get() ),
                                                                            15
                                                                        ),
                                                                5
                                                       )
                                      ),
                            23
                          ) ;
}

template < typename T > int foo( const T* p, std::size_t sz )
{
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7 } ;
    long long  b[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 } ;

    int n = 0 ;
    for( std::size_t i = 0 ; i < sz ; ++i )
    {
        if( i%2 == 0 )
        {
            if( contains( a, p[i] ? 3 : 9 ) ) n += 100 ;
            else n -= 8 ;
        }

        else
        {
            if( contains( b, p[i] ? 4LL : 7LL ) ) n += 100 ;
            else n -= 4 ;
        }
    }

    return n ;
}

int bar()
{
    char cstr8[35] = "vjvjvjbvkkbkvkvvjvjvjvjvjvjvjvj" ;
    char16_t cstr16[56] = u"vujufgufufufy" ;
    char32_t cstr32[7] = U"yfyfy" ;
    wchar_t wstr[22] = L"fcyyfhyffhyhfh" ;
    int a[45] = { 1, 45, 78, 999 } ;
    double d[67] = {0} ;
    short s[61] = { 10, 11, 12 } ;
    
    int n = 0 ;
    for( int i = 0 ; i < 10 ; ++i ) 
    {
        n += foo( cstr8, 12 ) + foo( cstr16, 32 ) + foo( cstr32, 8 ) ;
        n -= foo( wstr, 12 ) + foo( a, 13 ) + foo( d, 7 ) ;
        
        int temp = foo( s, 10+i ) ;
        if( temp > 5 ) n += 500 ;
        else n *= 7 ;
    }
    
    while( n < 10000 ) n += 79 ;

    while( n > 100000 ) n -= 979 ;

    return n ;
    
    /*
        movl $25000, %eax
    	retq    
    */
    
    // return 25000 ; // 10 * ( (12+32+8-12-13-7) * 100 + 500 )
}

