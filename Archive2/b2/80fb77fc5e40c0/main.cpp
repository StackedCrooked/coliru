#include <iostream>
#include <random>
#include <limits>

std::mt19937 mt;
int moare_random(const int nmax){
     std::uniform_int_distribution<uint32_t> uint(0,nmax);
     return(uint(mt));
}

int main(){
    const int seed=3,n=100;
    const double tol=std::numeric_limits<float>::min();
    std::mt19937 mt;
    mt.seed(seed);
    float x[n];
    for (int i=0; i<n; i++) x[i]=moare_random(9)*1.0f;
    int j=0;
    for(int i=0;i<n;i++)    j+=abs(x[i])<tol;
    std::cout<< j << std::endl;
    return 0;
}