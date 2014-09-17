#include <iostream>
#include <vector>
#include <string>

template <typename T>
struct NonSTLCollection {};

template <typename TSTLCollection>
struct STLCollectionShouldBeResizedAndReadByIndex
{
private:
    template <typename TItem>    
    static char f(NonSTLCollection<TItem>* pCollection);
    
    template <typename TItem>    
    static char f(std::basic_string<TItem>* pCollection);
    
    template <typename TItem>
    static char f(std::vector<TItem>* pCollection);
    
    static long f(...);
    
public:
    enum { value = sizeof(f((TSTLCollection*)0)) == sizeof(char) };
};

struct X : std::vector<int> {};
struct Y : std::string {};
struct Z {};

int main()
{
    std::cout << STLCollectionShouldBeResizedAndReadByIndex<X>::value << std::endl;
    std::cout << STLCollectionShouldBeResizedAndReadByIndex<std::vector<int> >::value << std::endl;
    std::cout << STLCollectionShouldBeResizedAndReadByIndex<std::string>::value << std::endl;
    std::cout << STLCollectionShouldBeResizedAndReadByIndex<Y>::value << std::endl;
    
    std::cout << STLCollectionShouldBeResizedAndReadByIndex<int>::value << std::endl;
    std::cout << STLCollectionShouldBeResizedAndReadByIndex<Z>::value << std::endl;
}
