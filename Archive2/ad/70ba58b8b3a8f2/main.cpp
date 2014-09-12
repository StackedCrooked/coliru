#include <iostream>
#include <memory>

struct Object { virtual ~Object() = default ; } ;
struct Drawable { virtual ~Drawable() = default ; } ;
struct StaticObject : Object, Drawable {} ;

#define SHOW(a) ( std::cout << #a << ": " << (a) << '\n' )

template < typename DERIVED, typename BASE > std::ptrdiff_t offsetofbase() // *** caution: not portable
{
    // **** assumes that 0x1000000 - sizeof(derived) to 0x1000000 are addresses
    // **** on which pointer arithmetic is well-defined
    // **** assumes that sizeof(derived) is < 16 MB
    const uintptr_t address = 0x1000000 ;
    const DERIVED* pderived = reinterpret_cast<const DERIVED*>(address) ;
    const BASE* pbase = pderived ;
    return reinterpret_cast<const char*>(pbase) - reinterpret_cast<const char*>(pderived) ;
}

int main()
{
    // these offsets are not guaranteed by the IS; but they are typical for 64-bit pointers
    SHOW( ( offsetofbase< StaticObject, Object >() ) ) ; // 0
    SHOW( ( offsetofbase< StaticObject, Drawable >() ) ) ; // 8

    /*
                 Typical object representation of StaticObject

                                            --------------
                                            |            |
                                            |            |
                                            |  Drawable  |
                                            |            |
                                            |            |
                        Drawable*  -------->--------------<--------- result of Drawable* converted to void*
                                            |            |
                                            |            |
                                            |  Object    |
                                            |            |
                                            |            |
                          Object*  -------->--------------<--------- result of Object* converted to void*

    */
}
