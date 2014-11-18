#include <iostream>
#include <utility>
#include <stddef.h>
#include <type_traits>


struct C {
    int16_t i;
    char  data[1];
};

template <class T>
struct B : C<T> {
    char footer;
};

int main(void)
{
    std::cout << "sizeof:" << std::endl;
    std::cout << "C<A>: " << sizeof(C<A>) << std::endl;
    std::cout << "C<A2>: " << sizeof(C<A2>) << std::endl;
    std::cout << "DIFFERENCE:\n";
    std::cout << "B<A>: " << sizeof(B<A>) << std::endl;
    std::cout << "B<A2>: " << sizeof(B<A2>) << std::endl;
    //std::cout << "B<A>::C: " << sizeof(B<A>::C) << std::endl;
    //std::cout << "B<A2>::C: " << sizeof(B<A2>::C) << std::endl;
    
    return 0;
}