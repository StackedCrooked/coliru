#include <iostream>

void test(int){}

template<typename T,typename...Args>
void test(int& sum,T v,Args... args)
{
    sum+=v;
    test(sum,args...);
}

using sum= test;
int main()
{
    int val=0;
    sum(val,4,7,6);
    std::cout<<val;
}
