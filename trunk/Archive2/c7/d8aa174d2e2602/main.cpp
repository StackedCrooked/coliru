#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

struct TypeInQuestion
{
    using type = int;    
};

struct OtherClass {};

template <class T>
struct enable_if_type
{
    using type = T;    
};

template <class T, class Enable = void>
struct has_type : std::false_type {};

template <class T>
struct has_type<T, enable_if_type<typename T::type> > : std::true_type {};

int main()
{
    std::cout << std::boolalpha;
    std::cout << has_type<TypeInQuestion>::value << std::endl;
    std::cout << has_type<OtherClass>::value << std::endl;
    //std::cout << has_type<int>::value << std::endl;
}
