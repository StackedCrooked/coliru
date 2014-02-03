#include <iostream>
using namespace std;

#define al *(char*)(eax_ptr)
int main()
{
    int eax = 0;
    int *eax_ptr = &eax;
    int edx = 0;
    char hh = 254;

    eax = hh;
    edx = al;
    
    cout << edx << endl;
}