#include <vector>
#include <iostream>

namespace MyNamespace
{
    template < typename T >
    struct InitializerList
    {
        std::vector<T> storage;
        
        template < typename... TT >
        InitializerList(TT&&... pp)
            : storage{pp...}
        {}
        
        decltype(storage.cbegin()) begin()
        {
            return storage.cbegin();
        }
        
        decltype(storage.cend()) end()
        {
            return storage.cend();
        }
    };
}

template<class T>
class ArrayPrinter
{
public:
    ArrayPrinter(MyNamespace::InitializerList<T> list)
    {
        for (auto i : list) std::cout << i << std::endl;
    }
};

int main()
{
    ArrayPrinter<int> ap{ {1,2,3} };
}


