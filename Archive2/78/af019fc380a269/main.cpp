#include <iostream>
#include <cstdint>

int main()
{
    const int32_t i = 5; // create a const memory

    int32_t* addr = const_cast<int32_t*>(&i); // convert the const pointer to a mutable memory pointer
    int32_t* addr2 = addr;
    
    *addr += 5; // sets 10 to its memory
    *addr2 += 5;
    
    std::cout << *addr << '\n' << *&i << '\n'; // shows the glory
    
    // shows address
    
    std::cout << addr << '\n' << &i;
    
    return 0;
}