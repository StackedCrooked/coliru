#include <iostream>
#include <random>
int morerandom(const int seednum,const int nmax)
{
     std::mt19937 mt;
     mt.seed(seednum);
     std::uniform_int_distribution<uint32_t> uint(0,nmax);
     return(uint(mt));
}


int main()
{
    const int seed=3;

    for (unsigned k=0; k<5; k++)
    {
        
        std::cout << morerandom(seed,10) << std::endl;
    }

    return 0;
}