#include <iostream>
#include <map>

//emulate MSVC's rand()
//this returns nonrandom results in the same
//range and distribution as MSVC's rand()
//as long as it's called a multiple of 32767 times;
#undef RAND_MAX
const int RAND_MAX = 32767;
int rand()
{
    static int i = 0;
    if (i == RAND_MAX)
        i = 0;
    return i++;
}


int main()
{
    std::map<int,int> m1,m2;
    int min=0,max=107;
    double dmin=min;
    double dmax=max;
    int resi;
    double u,d;
    for (int i=0; i<9993935; ++i){
        u=(double)rand();
        d=(double)RAND_MAX;
        double div= u/d;
        double res=div*(dmax-dmin+1);

        if(res<dmax+1){
            resi=(int)res;
            m1[resi]++;
        }
    }
    for (auto & i : m1)
        std::cout << i.first << " : " << i.second << '\n';    
}