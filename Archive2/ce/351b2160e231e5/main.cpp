#include <iostream>
#include <string>
#include <typeinfo>

    #ifdef __GNUG__
        #include <cxxabi.h>
        #include <memory>
        #include <cstdlib>

        std::string demangle( const char* name )
        {
            int status ;
            std::unique_ptr< char, decltype(&std::free) >
                cstr( abi::__cxa_demangle( name, nullptr, 0, &status ), &std::free ) ;
            return std::string( status == 0 ? cstr.get() : name ) ;
        }

    #elif defined _MSC_VER

        #include <cstring>

        std::string demangle( const char* name )
        {
            const auto p = std::strchr( name, ' ' ) ;
            return p ? p+1 : name ;
        }

    #else
        std::string demangle( const char* name ) { return name ; }
    #endif // __GNUG__

struct named
{
    virtual ~named() = default ;
    virtual std::string name() const { return demangle( typeid(*this).name() ) ; }
};

namespace Detail { struct IntermediateClass : named {}; }

class FinalClass : public named {} ;

int main()
{
    Detail::IntermediateClass ic ;
    FinalClass fc ;
    std::cout << ic.name() << "    " << fc.name() << '\n' ;
}
