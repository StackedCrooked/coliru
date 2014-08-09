#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main()
{
    int *P = new int(1);
    long int_repr_P = reinterpret_cast<long>(P);
    void *new_P = reinterpret_cast<void*>(P + sizeof(int));
    void *nn_P = reinterpret_cast<void*>(int_repr_P + sizeof(int)) ;
    cout << new_P << endl;
    cout << nn_P << endl;
}
