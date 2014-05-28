#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>    // std::copy    

int main() {
    const int n=1024;
    float a1[n],a2[n];
    std::srand(std::time(0)); 
    for(int i=0;i<n;i++)      a2[i]=std::rand()/(float)RAND_MAX;
    std::copy(a2,a2+n,a1);
    std::cout  << a1[0] << ", " << a2[0] << "\n";
}