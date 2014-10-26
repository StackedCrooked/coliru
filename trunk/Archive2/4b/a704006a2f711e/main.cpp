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

int foo( int v )
{
    static const int a[] = { 0, 1, 2, 3, 4, 5, 6, 7 } ;
    return contains( a, v ? 3 : 9 ) ? 1 : 99 ;

    /*
        movl $1, %eax
        ret
    */

    // return 1
}
