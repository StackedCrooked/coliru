#include <iostream>
#include <fstream>
#include <cstdlib>
int main()
{
    int  cptr[] = {10, 20, 30, 40, 50, 60};
    int * cptr2 = cptr;
    int * cptr3 = cptr;
    
    if( &cptr[0] == &cptr2[0] ) 
        std::cout << "cptr y cptr2, apuntan a misma direccion de memoria";
    
    std::cout << "\ncptr " << &*cptr << " == cptr2 " << &*cptr2;
    
    int * cptr4 = cptr2 + 5;
    cptr3 +=2; // equivalente cptr[2], cptr2[2] o, cptr + 2

    std::cout << "\n*&cptr4 :" << &*cptr4 << " val :" << cptr4[0];
    std::cout << "\ncptr3 += 2 :" << cptr3 << " val :" << *cptr3;
    // En la resta de dos punteros se obtiene el num de elementos desde a hacia b
    std::cout << "\ncptr3 - cptr2 :" << (cptr3 - cptr2);
}