#include <iostream>
#include <vector>

class A
{
public:
    int a, b;
};

template<typename T>
struct IsClass
{
    enum { Yes = std::is_class<T>::value };
    enum { No = !Yes };
};


int main()
{
    std::vector<A> v;
    auto it = v.begin();
    std::cout << IsClass<decltype(it)::value_type>::Yes << std::endl ;    
}
