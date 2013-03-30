#include <boost/preprocessor/cat.hpp>
#include <iostream>

template<class T>
struct Void { typedef void type; };


#define ENABLE_CHECK_TYPEDEF(Name) \
    template<class T, class U = void> \
    struct BOOST_PP_CAT(HasTypedef_, Name) { \
        enum { value = 0 }; \
    }; \
    template<class T> \
    struct BOOST_PP_CAT(HasTypedef_, Name)<T, typename Void<typename T::Name>::type> { \
        enum { value = 1  }; \
    };
    
    
#define HAS_TYPEDEF(Class, Name) static_cast<bool>(BOOST_PP_CAT(HasTypedef_, Name)<Class>::value)




struct Foo { struct Bar; };
struct Fuu { };


ENABLE_CHECK_TYPEDEF(Bar)


int main()
{
    std::cout << std::boolalpha;
    std::cout << "Foo::Bar => " << HAS_TYPEDEF(Foo, Bar) << std::endl;
    std::cout << "Fuu::Bar => " << HAS_TYPEDEF(Fuu, Bar) << std::endl;
}