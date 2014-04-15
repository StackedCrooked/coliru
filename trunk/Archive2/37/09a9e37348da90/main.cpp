#include <iostream>
#include <vector>

int main()
{
    std::vector<double> vec(1000) ; // vector of 1000 doubles
    
    std::cout << "object 'vec' takes up " << sizeof(vec) << " bytes " 
              << "at address " << std::addressof(vec) 
              << "\nit has an automatic storage duration (typically placed on the runtime-stack)\n" ;
              
    std::cout << "\nthe " << vec.size() << " objects of type double are dynamically allocated\n"
              << "they take up " << vec.size() * sizeof(double) << " bytes of memory "
              << "starting at address " << std::addressof( vec.front() ) 
              << "\nthe standard allocator allocates this memory from the free store\n" ;
}
