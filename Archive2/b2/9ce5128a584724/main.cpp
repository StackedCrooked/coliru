#include <cstdint>

int main()
{
    int* p =  nullptr;
    
    int pint = reinterpret_cast<std::uintptr_t>(p);
    
    (void)pint;
}