#include <iostream>
#include <math.h>


void foo(unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d)
{
    *a = 9;
    *b = 8;
    *c = 7;
    *d = 6;
}

void bar(int* a, int* b, int* c, int* d)
{
    *a = -9;
    *b = -8;
    *c = -7;
    *d = -6;
}


int main()
{
    int i[] = {1,2,3,4};
    unsigned int k[] = {-1,-2,-3,-4};
    std::cout << "i: " << i[0] << ", " << i[1] << ", " << i[2] << ", " << i[3] << std::endl;
    std::cout << "k: " << k[0] << ", " << k[1] << ", " << k[2] << ", " << k[3] << std::endl;
    
    foo((unsigned int*)i, (unsigned int*)i+1, (unsigned int*)i+2, (unsigned int*)i+3);
    foo(k, k+1, k+2, k+3);
    
    std::cout << "i: " << i[0] << ", " << i[1] << ", " << i[2] << ", " << i[3] << std::endl;
    std::cout << "k: " << k[0] << ", " << k[1] << ", " << k[2] << ", " << k[3] << std::endl;
    
    bar(i, i+1, i+2, i+3);
    bar((int*)k, (int*)k+1, (int*)k+2, (int*)k+3);
    
    std::cout << "i: " << i[0] << ", " << i[1] << ", " << i[2] << ", " << i[3] << std::endl;
    std::cout << "k: " << k[0] << ", " << k[1] << ", " << k[2] << ", " << k[3] << std::endl;
    
    
    return 0;
}