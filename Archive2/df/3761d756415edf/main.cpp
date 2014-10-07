#include <iostream>
#include <cstddef>

template<typename Flux, typename Object>                                                                                                                                                                                                       
struct IsPrintable
{
    typedef char yes[1];
    typedef char no[2];
    
    template <std::size_t U>
    struct SFINAE {};
    
    template <typename F, typename O>
    static yes& isPrintable(SFINAE<sizeof( *static_cast<F*>(NULL) << *static_cast<O*>(NULL) )>* = 0); 
    
    template <typename F, typename O>
    static no& isPrintable(...);
    
    static const bool value = sizeof(isPrintable<Flux, Object>(NULL)) == sizeof(yes);
};

struct Obj {};

struct Ok
{
    Ok& operator<<(Obj) { return *this; }
};

struct Nok {};

int main()
{
    std::cout << IsPrintable<Ok, Obj>::value << std::endl;
    
    std::cout << IsPrintable<Nok, Obj>::value << std::endl;
}
