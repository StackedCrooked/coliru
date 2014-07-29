#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <type_traits>

int main()
{
    typedef std::aligned_storage<sizeof(char), std::alignment_of<char>::value>::type storage_type;
    
    std::cout << "sizeof(A) = " <<  sizeof(char) << std::endl;
    std::cout << "std::alignment_of<A>::value = " <<  std::alignment_of<char>::value << std::endl;
    std::cout << "sizeof(storage_type) = " <<  sizeof(storage_type) << std::endl;
    
    size_t N = 5;
    
    //first get the aligned uninitialized memory!
    A *p1 = reinterpret_cast<char*>(new storage_type[N]);
    
    //then use placement new to construct the objects
    for(size_t i = 0; i < N ; i++)
        new (p1+i) char(i * 10);
        
    for(size_t i = 0; i < N ; i++)
       std::cout <<"Address = " << (p1+i) <<", s = " << p1[i] << std::endl;
}