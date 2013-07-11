#include <iostream>
#include <memory>

struct nop_delete
{
    template<typename T>
    void operator()( T * ) {}
};

template<typename T>
using weak_unique_ptr = std::unique_ptr<T, nop_delete>;

int main()
{
    std::unique_ptr<int> up( new int(42) );
    std::cout << *up << std::endl;
    
    weak_unique_ptr<int> wup( up.get(), nop_delete{} );
    std::cout << *wup << std::endl;
}
