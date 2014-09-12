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
              Drawable*  pdrawable -------->--------------<--------- void* pvd = pdrawable (Drawable* converted to void*)
                                            |            |
                                            |            |
                                            |  Object    |
                                            | (8 bytes)  |
                                            |            |
                                            |            |
                   Object* pobject -------->--------------<--------- void* pvo = pobject (Object* converted to void*)

    */

    std::cout << '\n' ;
    StaticObject so ;
    Object* pobject = std::addressof(so) ;
    SHOW(pobject) ;

    void* pvo = pobject ;
    SHOW(pvo) ;

    std::cout << '\n' ;
    Drawable* pdrawable = std::addressof(so) ;
    SHOW(pdrawable) ;
    void* pvd = pdrawable ;
    SHOW(pvd) ;

    std::cout << '\n' ;
    SHOW( (Drawable*)pvo ) ; // *** wrong *** C-style cast is interpreted as static_cast<Drawable*>(pvo)
    SHOW( (Drawable*)pobject ) ; // *** wrong *** C-style cast is interpreted as reinterpret_cast<Drawable*>(pobject)
    SHOW( ( dynamic_cast<Drawable*>(pobject) ) ) ; // fine; type-safe run-time dynamic cross-cast
}
