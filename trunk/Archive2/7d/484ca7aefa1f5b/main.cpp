#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main()
{
    int *P = new int(1); //Safely-derived pointer
    uint64_t p_int = reinterpret_cast<uint64_t>(P); 
    uint64_t new_p_int = p_int + 10; // Result of an additive operation
    void *new_P = reinterpret_cast<void*>(new_p_int);
    void *P_computed_from_void_star = reinterpret_cast<void*>(P) + 10;
    cout << "P converted to void* = " << P_computed_from_void_star << endl;
    cout << "P after result of an additive operation = " << new_P << endl;
}
