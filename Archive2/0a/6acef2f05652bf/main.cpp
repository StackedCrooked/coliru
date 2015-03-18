#include <iostream>
#include <cstdint>

int main()
{
    const int32_t i = 5; // create a const memory

    int32_t* addr = const_cast<int32_t*>(&i); // convert the const pointer to a mutable memory pointer
    
    *addr = 10; // sets 10 to its memory
    
    std::cout << *addr << '\n' << i; // shows the glory
    
    return 0;
}