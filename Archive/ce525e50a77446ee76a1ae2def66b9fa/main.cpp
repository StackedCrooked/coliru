#include <iostream>
#include <new>

int main()
{
    int *p = nullptr;
    size_t i = 0;
    
    while( ( p = new(std::nothrow)int[1024*1024*10] ) != nullptr ) {
        std::cout << ++i << std::endl;
    }
}
