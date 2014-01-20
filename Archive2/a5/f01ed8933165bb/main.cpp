#include <iostream>

int main()
{
    int i{ 5 };

    void* v = &i;

    int* t = reinterpret_cast<int*>(v);
    int u = reinterpret_cast<int&>(v);

 std::cout << *t << std::endl ;
 std::cout << u << std::endl ;
 std::cout << std::hex << v << std::endl ;

}