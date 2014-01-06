#include <iostream>

int main ()
{
    auto lst = { 10, 11, 12, 13 } ;

    for( int v : lst ) std::cout << v << ' ' ; // 10 11 12 13 
    
    std::cout << "(size " << lst.size() << ")\n" ; // (size 4)
    
    std::cout << lst.begin()[2] << '\n' ; // 12
}
