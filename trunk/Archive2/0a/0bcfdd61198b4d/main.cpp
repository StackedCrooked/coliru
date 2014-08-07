#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main()
{
    int *P = new int(1);
    long p_int = reinterpret_cast<long>(P);
    long new_p_int = p_int + 10;
    void *new_P = reinterpret_cast<void*>(new_p_int);
    void *P_cpnverting_to_void = reinterpret_cast<void*>(P);
    cout << "P converted to void* = " << P_cpnverting_to_void << endl;
    cout << "P after result of an additive operation = " << new_P << endl;
}
