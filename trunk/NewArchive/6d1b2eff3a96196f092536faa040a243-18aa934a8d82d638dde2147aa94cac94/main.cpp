#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <type_traits>


struct A
{
    int  a;
    char b;
    
    A (int a) : a(a) {}
};

int main()
{
    typedef std::aligned_storage<sizeof(A), std::alignment_of<A>::value>::type storage_type;
    
    std::cout << "sizeof(A) = " <<  sizeof(A) << std::endl;
    std::cout << "std::alignment_of<A>::value = " <<  std::alignment_of<A>::value << std::endl;
    std::cout << "sizeof(storage_type) = " <<  sizeof(storage_type) << std::endl;
    
    size_t N = 5;
    
    //first get the aligned uninitialized memory!
    A *p1 = reinterpret_cast<A*>(new storage_type[N]);
    
    //then use placement new to construct the objects
    for(size_t i = 0; i < N ; i++)
        new (p1+i) A(i * 10);
        
    for(size_t i = 0; i < N ; i++)
       std::cout <<"Address = " << (p1+i) <<", A.a = " << p1[i].a << std::endl;
}