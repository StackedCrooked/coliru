#include <iostream>


#define CAN_HAS(Name) \
    template <typename T> \
    struct CanHas_##Name { \
        typedef char yes[1]; \
        typedef char no[2]; \
        template <typename C> static yes& test(typename C::Name*); \
        template <typename> static no& test(...); \
        static const bool value = sizeof(test<T>(0)) == sizeof(yes);\
    };

#define HAS(Type, Name) static_cast<bool>(CanHas_##Name<Type>::value)


template<typename> struct traits;


//
// loltraits
//
struct lol {};
template<> struct traits<lol> { typedef int cheezburger; };


//
// notloltraits
//
struct notlol {};
template<> struct traits<notlol> { typedef int cake; };


CAN_HAS(cheezburger)


int main()
{   
    
    std::cout << "lol " << (HAS(traits<lol>, cheezburger) ? "+1" : "-1") << std::endl;
    std::cout << "notlol " << (HAS(traits<notlol>, cheezburger) ? "+1" : "-1") << std::endl;
}
