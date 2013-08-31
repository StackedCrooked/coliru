#include <iostream>
#include <chrono>
inline short toBigEndian(short i)
{
    return (i<<8)|(i>>8);
}
short (*toBigEndianPtr)(short i)=toBigEndian;
int main()
{  
    std::chrono::duration<double> t;
    int total=0;
    for(int i=0;i<100000;i++)
    {
        auto begin=std::chrono::high_resolution_clock::now();
        short a=toBigEndianPtr((short)i);//toBigEndianPtr((short)i);
        total+=a;
        auto end=std::chrono::high_resolution_clock::now();
        t+=std::chrono::duration_cast<std::chrono::duration<double>>(end-begin);
    }
    std::cout<<t.count()<<", "<<total<<std::endl;
    return 0;
}